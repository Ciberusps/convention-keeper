// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionCoverage.h"
#include "ConventionKeeperConvention_Base.h"
#include "ConventionKeeperBlueprintLibrary.h"
#include "Development/ConventionKeeperSettings.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"
#include "Rules/ConventionKeeperRule_AssetPlacement.h"

#include "AssetRegistry/ARFilter.h"
#include "AssetRegistry/AssetRegistryHelpers.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Logging/MessageLog.h"
#include "Misc/PackageName.h"
#include "UObject/Class.h"

#define LOCTEXT_NAMESPACE "ConventionCoverage"

struct FCoveredRuleScope
{
	UConventionKeeperRule* Rule = nullptr;
	FString RulePath;
};

static void CollectCoveredAssetPaths(
	IAssetRegistry& AssetRegistry,
	const TArray<FString>& ResolvedNormPaths,
	const TArray<FString>& SelectedPaths,
	const TArray<TSubclassOf<UObject>>& AssetClasses,
	const TArray<FString>& AssetClassPaths,
	TSet<FString>& OutCovered,
	TMap<FString, TArray<FCoveredRuleScope>>* OutCoveredByRules,
	UConventionKeeperRule* Rule)
{
	TArray<FAssetNamingScopeEntry> Scopes = UConventionKeeperRule_AssetNaming::GetScopesForValidation(ResolvedNormPaths, SelectedPaths);
	for (const FAssetNamingScopeEntry& Scope : Scopes)
	{
		FString PackagePath = FString(TEXT("/Game/")) + (Scope.QueryPath.Len() > 8 ? Scope.QueryPath.Mid(8) : FString());
		PackagePath.ReplaceInline(TEXT("\\"), TEXT("/"));
		if (PackagePath.EndsWith(TEXT("/")))
		{
			PackagePath.LeftChopInline(1);
		}
		if (PackagePath.Len() <= 5)
		{
			continue;
		}

		FARFilter Filter;
		Filter.PackagePaths.Add(FName(*PackagePath));
		Filter.bRecursivePaths = true;
		for (TSubclassOf<UObject> Class : AssetClasses)
		{
			if (Class.Get())
			{
				Filter.ClassPaths.Add(FTopLevelAssetPath(Class.Get()));
			}
		}
		for (const FString& ClassPath : AssetClassPaths)
		{
			if (ClassPath.IsEmpty())
			{
				continue;
			}
			UClass* LoadedClass = UClass::TryFindTypeSlow<UClass>(*ClassPath, EFindFirstObjectOptions::ExactClass);
			if (LoadedClass)
			{
				Filter.ClassPaths.Add(FTopLevelAssetPath(LoadedClass));
			}
			else if (ClassPath.Contains(TEXT(".")))
			{
				Filter.ClassPaths.Add(FTopLevelAssetPath(ClassPath));
			}
		}
		if (Filter.ClassPaths.IsEmpty())
		{
			continue;
		}

		TArray<FAssetData> AssetDataList;
		AssetRegistry.GetAssets(Filter, AssetDataList);
		for (const FAssetData& A : AssetDataList)
		{
			FString ObjectPath = A.GetSoftObjectPath().ToString();
			OutCovered.Add(ObjectPath);
			if (OutCoveredByRules && Rule)
			{
				TArray<FCoveredRuleScope>& RuleScopes = OutCoveredByRules->FindOrAdd(ObjectPath);
				bool bAlreadyAdded = false;
				for (const FCoveredRuleScope& Existing : RuleScopes)
				{
					if (Existing.Rule == Rule && Existing.RulePath == Scope.RulePath)
					{
						bAlreadyAdded = true;
						break;
					}
				}
				if (!bAlreadyAdded)
				{
					FCoveredRuleScope RuleScope;
					RuleScope.Rule = Rule;
					RuleScope.RulePath = Scope.RulePath;
					RuleScopes.Add(MoveTemp(RuleScope));
				}
			}
		}
	}
}

static void ResolveRulePaths(
	const FString& PatternPathIn,
	const TMap<FString, FString>& PlaceholdersWithBraces,
	TArray<FString>& OutResolvedNormPaths)
{
	FString PatternPath = PatternPathIn;
	PatternPath.ReplaceInline(TEXT("\\"), TEXT("/"));
	while (PatternPath.StartsWith(TEXT("/")))
	{
		PatternPath.RemoveFromStart(TEXT("/"));
	}
	if (PatternPath.IsEmpty())
	{
		PatternPath = TEXT("Content/{ProjectName}");
	}

	TArray<FString> ResolvedPaths = UConventionKeeperBlueprintLibrary::ResolveTemplatePaths(PatternPath, PlaceholdersWithBraces);
	if (ResolvedPaths.Num() == 0)
	{
		TSet<FString> TemplateNames = UConventionKeeperBlueprintLibrary::ExtractTemplatesFromPath(PatternPath, PlaceholdersWithBraces);
		if (TemplateNames.Num() == 0)
		{
			FString SinglePath = PatternPath;
			for (const TTuple<FString, FString>& Pair : PlaceholdersWithBraces)
			{
				SinglePath = SinglePath.Replace(*Pair.Key, *Pair.Value, ESearchCase::CaseSensitive);
			}
			SinglePath.ReplaceInline(TEXT("\\"), TEXT("/"));
			SinglePath.TrimStartAndEndInline();
			while (SinglePath.StartsWith(TEXT("/")))
			{
				SinglePath.RemoveFromStart(TEXT("/"));
			}
			if (!SinglePath.IsEmpty())
			{
				if (!SinglePath.StartsWith(TEXT("Content/")))
				{
					SinglePath = FString(TEXT("Content/")) + SinglePath;
				}
				ResolvedPaths.Add(FString(TEXT("/")) + SinglePath);
			}
		}
	}

	TArray<FString> PatternSegments;
	PatternPath.ParseIntoArray(PatternSegments, TEXT("/"), true);
	const int32 PatternSegmentCount = PatternSegments.Num();

	for (const FString& ResolvedPathWithSlash : ResolvedPaths)
	{
		FString ResolvedPath = ResolvedPathWithSlash;
		ResolvedPath.ReplaceInline(TEXT("\\"), TEXT("/"));
		if (ResolvedPath.StartsWith(TEXT("/")))
		{
			ResolvedPath.RemoveFromStart(TEXT("/"));
		}
		if (!ResolvedPath.StartsWith(TEXT("Content/")))
		{
			ResolvedPath = FString(TEXT("Content/")) + ResolvedPath;
		}
		TArray<FString> Segments;
		ResolvedPath.ParseIntoArray(Segments, TEXT("/"), true);
		if (Segments.Num() != PatternSegmentCount)
		{
			continue;
		}
		OutResolvedNormPaths.Add(UConventionKeeperRule::NormalizeRelativePath(ResolvedPath));
	}
}

FConventionCoverageResult ConventionCoverage::RunAnalysis(
	UConventionKeeperConvention_Base* Convention,
	const UConventionKeeperSettings* Settings,
	const TArray<FString>& SelectedPaths)
{
	FConventionCoverageResult Result;

	if (!Convention || !Settings)
	{
		return Result;
	}

	TMap<FString, FString> PlaceholdersWithBraces;
	{
		TMap<FString, FString> FromSettings = Settings->GetPlaceholders();
		for (const TTuple<FString, FString>& Pair : FromSettings)
		{
			FString Key = Pair.Key;
			if (!Key.StartsWith(TEXT("{")))
			{
				Key = FString::Printf(TEXT("{%s}"), *Pair.Key);
			}
			PlaceholdersWithBraces.Add(Key, Pair.Value);
		}
	}

	auto PackagePathToContentPath = [](const FString& PackagePath) -> FString
	{
		FString Path = PackagePath;
		Path.ReplaceInline(TEXT("\\"), TEXT("/"));
		if (Path.StartsWith(TEXT("/Game/")))
		{
			return FString(TEXT("Content/")) + Path.Mid(6);
		}
		return FString(TEXT("Content")) + Path;
	};

	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();
	TSet<FString> CoveredSet;
	TMap<FString, TArray<FCoveredRuleScope>> CoveredByRules;

	TArray<UConventionKeeperRule*> EffectiveRules = Convention->GetEffectiveRules();

	for (UConventionKeeperRule* Rule : EffectiveRules)
	{
		if (!Rule)
		{
			continue;
		}
		UConventionKeeperRule_AssetNaming* NamingRule = Cast<UConventionKeeperRule_AssetNaming>(Rule);
		UConventionKeeperRule_AssetPlacement* PlacementRule = Cast<UConventionKeeperRule_AssetPlacement>(Rule);
		FString PatternPath;
		TArray<TSubclassOf<UObject>> AssetClasses;
		TArray<FString> AssetClassPaths;
		if (NamingRule)
		{
			PatternPath = NamingRule->FolderPathPattern.Path;
			AssetClasses = NamingRule->AssetClasses;
			AssetClassPaths = NamingRule->AssetClassPaths;
		}
		else if (PlacementRule)
		{
			PatternPath = PlacementRule->FolderPathPattern.Path;
			AssetClasses = PlacementRule->AssetClasses;
			AssetClassPaths = PlacementRule->AssetClassPaths;
		}
		else
		{
			continue;
		}
		if (AssetClasses.Num() == 0 && AssetClassPaths.Num() == 0)
		{
			continue;
		}

		TArray<FString> ResolvedNormPaths;
		ResolveRulePaths(PatternPath, PlaceholdersWithBraces, ResolvedNormPaths);
		if (ResolvedNormPaths.IsEmpty())
		{
			continue;
		}

		CollectCoveredAssetPaths(AssetRegistry, ResolvedNormPaths, SelectedPaths, AssetClasses, AssetClassPaths, CoveredSet, &CoveredByRules, Rule);
	}

	FARFilter AllFilter;
	AllFilter.PackagePaths.Add(FName(TEXT("/Game")));
	AllFilter.bRecursivePaths = true;
	TArray<FAssetData> AllAssets;
	AssetRegistry.GetAssets(AllFilter, AllAssets);

	TMap<FString, TPair<int32, int32>> ClassToTotalAndCovered;
	TMap<FString, TPair<FAssetData, FString>> CoveredAssetDataAndClass;

	for (const FAssetData& A : AllAssets)
	{
		FString PackageName = A.PackageName.ToString();
		FString ContentPath = PackagePathToContentPath(PackageName);
		if (Settings->Exclusions.Num() > 0
			&& UConventionKeeperRule_AssetNaming::IsPathUnderExcluded(ContentPath, Settings->Exclusions, PlaceholdersWithBraces))
		{
			continue;
		}

		FString ClassKey = A.AssetClassPath.GetAssetName().ToString();
		if (ClassKey.IsEmpty())
		{
			ClassKey = A.AssetClassPath.ToString();
		}

		TPair<int32, int32>& Counts = ClassToTotalAndCovered.FindOrAdd(ClassKey, TPair<int32, int32>(0, 0));
		Counts.Key++;
		Result.TotalAssets++;

		FString ObjectPath = A.GetSoftObjectPath().ToString();
		if (CoveredSet.Contains(ObjectPath))
		{
			Counts.Value++;
			Result.CoveredAssets++;
			CoveredAssetDataAndClass.Add(ObjectPath, TPair<FAssetData, FString>(A, ClassKey));
		}
	}

	auto IsAssetCompliantForRule = [&PlaceholdersWithBraces](
		const FAssetData& AssetData,
		const FString& ContentFolderPath,
		const FCoveredRuleScope& RuleScope) -> bool
	{
		UConventionKeeperRule* Rule = RuleScope.Rule;
		UConventionKeeperRule_AssetNaming* NamingRule = Cast<UConventionKeeperRule_AssetNaming>(Rule);
		UConventionKeeperRule_AssetPlacement* PlacementRule = Cast<UConventionKeeperRule_AssetPlacement>(Rule);
		if (NamingRule)
		{
			TMap<FString, FString> PathPlaceholders;
			FString PatternPath = NamingRule->FolderPathPattern.Path;
			PatternPath.ReplaceInline(TEXT("\\"), TEXT("/"));
			while (PatternPath.StartsWith(TEXT("/"))) PatternPath.RemoveFromStart(TEXT("/"));
			if (PatternPath.IsEmpty()) PatternPath = TEXT("Content/{ProjectName}");
			if (!UConventionKeeperRule_AssetNaming::ExtractPathPlaceholders(PatternPath, RuleScope.RulePath, PlaceholdersWithBraces, PathPlaceholders))
			{
				return false;
			}
			bool bValid = false;
			NamingRule->EvaluateSingleAssetNaming(AssetData, PathPlaceholders, bValid, nullptr, nullptr);
			return bValid;
		}
		if (PlacementRule)
		{
			FString PathWithSlash = ContentFolderPath;
			if (!PathWithSlash.EndsWith(TEXT("/"))) PathWithSlash += TEXT("/");
			return UConventionKeeperRule_AssetPlacement::PathContainsSegment(PathWithSlash, PlacementRule->RequiredPathSegment);
		}
		return true;
	};

	TMap<FString, int32> ClassCompliant;
	for (const TTuple<FString, TArray<FCoveredRuleScope>>& Pair : CoveredByRules)
	{
		const FString& ObjectPath = Pair.Key;
		const TPair<FAssetData, FString>* AssetAndClass = CoveredAssetDataAndClass.Find(ObjectPath);
		if (!AssetAndClass)
		{
			continue;
		}
		FString ContentPath = PackagePathToContentPath(AssetAndClass->Key.PackagePath.ToString());
		bool bAllPass = true;
		for (const FCoveredRuleScope& CoveredRuleScope : Pair.Value)
		{
			if (CoveredRuleScope.Rule && !IsAssetCompliantForRule(AssetAndClass->Key, ContentPath, CoveredRuleScope))
			{
				bAllPass = false;
				break;
			}
		}
		if (bAllPass)
		{
			Result.CompliantAssets++;
			ClassCompliant.FindOrAdd(AssetAndClass->Value, 0)++;
		}
	}

	for (const TTuple<FString, TPair<int32, int32>>& Pair : ClassToTotalAndCovered)
	{
		FConventionCoverageClassStats Stats;
		Stats.ClassName = Pair.Key;
		Stats.Total = Pair.Value.Key;
		Stats.Covered = Pair.Value.Value;
		Stats.Compliant = ClassCompliant.FindRef(Pair.Key);
		Result.PerClass.Add(Stats);
	}
	Result.PerClass.Sort([](const FConventionCoverageClassStats& A, const FConventionCoverageClassStats& B)
	{
		return A.Total > B.Total;
	});

	return Result;
}

void ConventionCoverage::ReportToMessageLog(
	const FConventionCoverageResult& Result,
	EConventionReportMode Mode,
	bool bOpenLog)
{
	FMessageLog ConventionLog(TEXT("ConventionKeeper"));
	const bool bCoverageMode = Mode == EConventionReportMode::CoverageOnly || Mode == EConventionReportMode::CoverageAndCompliance;
	const bool bComplianceMode = Mode == EConventionReportMode::ComplianceOnly || Mode == EConventionReportMode::CoverageAndCompliance;

	if (Mode == EConventionReportMode::CoverageOnly)
	{
		ConventionLog.NewPage(LOCTEXT("CoverageLogPage", "Convention Rule Coverage"));
	}
	else if (Mode == EConventionReportMode::ComplianceOnly)
	{
		ConventionLog.NewPage(LOCTEXT("ComplianceLogPage", "Convention Compliance"));
	}
	else
	{
		ConventionLog.NewPage(LOCTEXT("CoverageComplianceLogPage", "Convention Coverage & Compliance"));
	}

	const int32 Total = Result.TotalAssets;
	const int32 Covered = Result.CoveredAssets;
	const int32 Compliant = Result.CompliantAssets;
	const int32 CoveragePct = Total > 0 ? FMath::RoundToInt(100.0 * Covered / Total) : 0;
	const int32 CompliancePct = Covered > 0 ? FMath::RoundToInt(100.0 * Compliant / Covered) : 0;

	if (bCoverageMode)
	{
		ConventionLog.Info(FText::Format(
			LOCTEXT("CoverageSummary", "In rule scope: {0}% of assets ({1}/{2}) are in a path where a rule applies."),
			FText::AsNumber(CoveragePct), FText::AsNumber(Covered), FText::AsNumber(Total)));
	}
	if (bComplianceMode)
	{
		ConventionLog.Info(FText::Format(
			LOCTEXT("ComplianceSummary", "Compliance: of those in scope, {0}% ({1}/{2}) pass validation."),
			FText::AsNumber(CompliancePct), FText::AsNumber(Compliant), FText::AsNumber(Covered)));
	}

	constexpr int32 LowComplianceThreshold = 10;

	for (const FConventionCoverageClassStats& Stats : Result.PerClass)
	{
		const int32 ClassCoveragePct = Stats.Total > 0 ? static_cast<int32>(FMath::RoundToInt(100.0 * Stats.Covered / Stats.Total)) : 0;
		const int32 ClassCompliancePct = Stats.Covered > 0 ? static_cast<int32>(FMath::RoundToInt(100.0 * Stats.Compliant / Stats.Covered)) : 0;
		FText Message;
		const bool bNoCoverage = (Stats.Covered == 0 && Stats.Total > 0);
		const bool bLowOrZeroCompliance = (Stats.Covered > 0 && ClassCompliancePct <= LowComplianceThreshold);

		if (Mode == EConventionReportMode::CoverageOnly)
		{
			if (bNoCoverage)
			{
				Message = FText::Format(
					LOCTEXT("CoverageClassUncovered", "Class \"{0}\": {1} assets, no rule applies (add a rule for this class)."),
					FText::FromString(Stats.ClassName), FText::AsNumber(Stats.Total));
				ConventionLog.Warning(Message);
			}
			else
			{
				Message = FText::Format(
					LOCTEXT("CoverageClassOnly", "Class \"{0}\": {1} total; {2} in scope ({3}%)."),
					FText::FromString(Stats.ClassName), FText::AsNumber(Stats.Total), FText::AsNumber(Stats.Covered),
					FText::AsNumber(ClassCoveragePct));
				ConventionLog.Info(Message);
			}
			continue;
		}

		if (Mode == EConventionReportMode::ComplianceOnly)
		{
			if (Stats.Covered == 0)
			{
				continue;
			}
			Message = FText::Format(
				LOCTEXT("ComplianceClassOnly", "Class \"{0}\": {1} in scope; {2}% compliant ({3}/{1})."),
				FText::FromString(Stats.ClassName), FText::AsNumber(Stats.Covered),
				FText::AsNumber(ClassCompliancePct), FText::AsNumber(Stats.Compliant));
			if (bLowOrZeroCompliance)
			{
				ConventionLog.Warning(Message);
			}
			else
			{
				ConventionLog.Info(Message);
			}
			continue;
		}

		if (bNoCoverage)
		{
			Message = FText::Format(
				LOCTEXT("CoverageClassWithComplianceUncovered", "Class \"{0}\": {1} assets, no rule applies (add a rule for this class)."),
				FText::FromString(Stats.ClassName), FText::AsNumber(Stats.Total));
			ConventionLog.Warning(Message);
		}
		else
		{
			Message = FText::Format(
				LOCTEXT("CoverageClassWithCompliance", "Class \"{0}\": {1} total; {2} in scope ({3}%); of those in scope, {4}% compliant ({5}/{2})."),
				FText::FromString(Stats.ClassName), FText::AsNumber(Stats.Total), FText::AsNumber(Stats.Covered),
				FText::AsNumber(ClassCoveragePct), FText::AsNumber(ClassCompliancePct), FText::AsNumber(Stats.Compliant));
			if (bLowOrZeroCompliance)
			{
				ConventionLog.Warning(Message);
			}
			else
			{
				ConventionLog.Info(Message);
			}
		}
	}

	if (bOpenLog)
	{
		ConventionLog.Open(EMessageSeverity::Info, true);
	}
}

#undef LOCTEXT_NAMESPACE
