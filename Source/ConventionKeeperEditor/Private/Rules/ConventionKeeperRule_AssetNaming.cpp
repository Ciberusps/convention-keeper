// Pavel Penkov 2025 All Rights Reserved.

#include "Rules/ConventionKeeperRule_AssetNaming.h"

#include "AssetRegistry/ARFilter.h"
#include "Localization/ConventionKeeperLocalization.h"
#include "Rules/ConventionKeeperRule.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "ConventionKeeperBlueprintLibrary.h"
#include "Development/ConventionKeeperSettings.h"
#include "Misc/Paths.h"
#include "Misc/PackageName.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperRule_AssetNaming)

FString UConventionKeeperRule_AssetNaming::NormalizeRelativePath(const FString& InPath)
{
	return UConventionKeeperRule::NormalizeRelativePath(InPath);
}

namespace AssetNamingPathHelpers
{
FString LiteralPrefixOfPath(const FString& NormalizedPath)
{
	TArray<FString> Segments;
	NormalizedPath.ParseIntoArray(Segments, TEXT("/"), true);
	FString Prefix;
	for (const FString& Seg : Segments)
	{
		if (Seg.Contains(TEXT("{")))
		{
			break;
		}
		if (!Prefix.IsEmpty())
		{
			Prefix += TEXT("/");
		}
		Prefix += Seg;
	}
	if (!Prefix.IsEmpty())
	{
		Prefix += TEXT("/");
	}
	return Prefix;
}

FString SelectedPathAsContentForm(const FString& InPath)
{
	FString Path = InPath;
	Path.ReplaceInline(TEXT("\\"), TEXT("/"));
	Path.TrimStartAndEndInline();
	const FString ProjectDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()).Replace(TEXT("\\"), TEXT("/"));
	if (Path.StartsWith(ProjectDir))
	{
		Path = Path.Mid(ProjectDir.Len());
	}
	else
	{
		const FString ContentMarker = TEXT("/Content/");
		const int32 ContentPos = Path.Find(ContentMarker);
		if (ContentPos != INDEX_NONE)
		{
			Path = FString(TEXT("Content/")) + Path.Mid(ContentPos + ContentMarker.Len());
		}
	}
	while (Path.StartsWith(TEXT("/")))
	{
		Path.RemoveFromStart(TEXT("/"));
	}
	if (Path.StartsWith(TEXT("All/")))
	{
		Path.RemoveFromStart(TEXT("All/"));
	}
	if (Path.StartsWith(TEXT("Game/")))
	{
		Path = FString(TEXT("Content/")) + Path.Mid(5);
	}
	const int32 DotPos = Path.Find(TEXT("."), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	if (DotPos != INDEX_NONE)
	{
		const FString Ext = Path.Mid(DotPos + 1).ToLower();
		if (Ext == TEXT("uasset") || Ext == TEXT("umap"))
		{
			Path = Path.Left(DotPos);
		}
	}
	if (!Path.EndsWith(TEXT("/")))
	{
		Path += TEXT("/");
	}
	return Path;
}
}

bool UConventionKeeperRule_AssetNaming::IsRelevantPath(const FString& ResolvedPath, const TArray<FString>& SelectedPaths)
{
	return IsRelevantPath(TArray<FString>{NormalizeRelativePath(ResolvedPath)}, SelectedPaths);
}

bool UConventionKeeperRule_AssetNaming::IsRelevantPath(const TArray<FString>& ResolvedPathsToCheck, const TArray<FString>& SelectedPaths)
{
	if (SelectedPaths.IsEmpty())
	{
		return true;
	}
	for (const FString& ResolvedPath : ResolvedPathsToCheck)
	{
		FString PathForCompare = ResolvedPath;
		PathForCompare.ReplaceInline(TEXT("\\"), TEXT("/"));
		while (PathForCompare.StartsWith(TEXT("/")))
		{
			PathForCompare.RemoveFromStart(TEXT("/"));
		}
		const FString NormalizedResolvedPath = NormalizeRelativePath(PathForCompare);
		for (const FString& SelectedPath : SelectedPaths)
		{
			const FString NormalizedSelectedPath = AssetNamingPathHelpers::SelectedPathAsContentForm(SelectedPath);
			if (NormalizedResolvedPath.StartsWith(NormalizedSelectedPath) || NormalizedSelectedPath.StartsWith(NormalizedResolvedPath))
			{
				return true;
			}
		}
	}
	return false;
}

bool UConventionKeeperRule_AssetNaming::IsPathUnderExcluded(const FString& ResolvedPath, const TArray<FString>& Exclusions, const TMap<FString, FString>& Placeholders)
{
	const FString NormalizedPath = NormalizeRelativePath(ResolvedPath);
	for (const FString& Exclusion : Exclusions)
	{
		FString ResolvedExclude = Exclusion;
		for (const TTuple<FString, FString>& Pair : Placeholders)
		{
			ResolvedExclude = ResolvedExclude.Replace(*Pair.Key, *Pair.Value, ESearchCase::CaseSensitive);
		}
		ResolvedExclude.ReplaceInline(TEXT("\\"), TEXT("/"));
		ResolvedExclude.TrimStartAndEndInline();
		const bool bExclusionIsFolder = ResolvedExclude.EndsWith(TEXT("/"));
		FString NormalizedExclude = bExclusionIsFolder ? NormalizeRelativePath(ResolvedExclude) : ResolvedExclude;
		if (bExclusionIsFolder)
		{
			if (NormalizedPath.StartsWith(NormalizedExclude) || NormalizedExclude.StartsWith(NormalizedPath))
			{
				return true;
			}
		}
		else
		{
			if (NormalizedPath == NormalizedExclude + TEXT("/") || NormalizedPath.StartsWith(NormalizedExclude + TEXT("/")))
			{
				return true;
			}
		}
	}
	return false;
}

bool UConventionKeeperRule_AssetNaming::ExtractPathPlaceholders(const FString& PatternPath, const FString& ResolvedPath, const TMap<FString, FString>& GlobalPlaceholders, TMap<FString, FString>& OutPathPlaceholders)
{
	return UConventionKeeperBlueprintLibrary::ExtractPathPlaceholders(PatternPath, ResolvedPath, GlobalPlaceholders, OutPathPlaceholders);
}

FString UConventionKeeperRule_AssetNaming::ResolveNamingTemplate(const FString& Template, const TMap<FString, FString>& PathPlaceholders)
{
	FString Result = Template;
	for (const TTuple<FString, FString>& Pair : PathPlaceholders)
	{
		Result = Result.Replace(*FString::Printf(TEXT("{%s}"), *Pair.Key), *Pair.Value, ESearchCase::CaseSensitive);
	}
	return Result;
}

bool UConventionKeeperRule_AssetNaming::IsNumberSuffixValid(const FString& AssetName, int32 PaddingDigits)
{
	if (PaddingDigits <= 0 || AssetName.IsEmpty())
	{
		return true;
	}
	int32 i = AssetName.Len() - 1;
	while (i >= 0 && FChar::IsDigit(AssetName[i]))
	{
		--i;
	}
	const int32 SuffixStart = i + 1;
	if (SuffixStart >= AssetName.Len())
	{
		return true;
	}
	FString Suffix = AssetName.Mid(SuffixStart);
	return Suffix.Len() == PaddingDigits;
}

FString UConventionKeeperRule_AssetNaming::SuggestZeroPaddedName(const FString& AssetName, int32 PaddingDigits)
{
	if (PaddingDigits <= 0 || AssetName.IsEmpty())
	{
		return AssetName;
	}
	int32 i = AssetName.Len() - 1;
	while (i >= 0 && FChar::IsDigit(AssetName[i]))
	{
		--i;
	}
	const int32 SuffixStart = i + 1;
	if (SuffixStart >= AssetName.Len())
	{
		return AssetName;
	}
	FString NumPart = AssetName.Mid(SuffixStart);
	int32 Val = 0;
	for (TCHAR c : NumPart)
	{
		Val = Val * 10 + (c - TEXT('0'));
	}
	FString Padded = FString::Printf(TEXT("%0*d"), PaddingDigits, Val);
	const FString Prefix = AssetName.Left(SuffixStart);
	if (SuffixStart > 0 && AssetName[SuffixStart - 1] == '_')
	{
		return Prefix + Padded;
	}
	return Prefix + TEXT("_") + Padded;
}

bool UConventionKeeperRule_AssetNaming::CanValidate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const
{
	FString PatternPath = FolderPathPattern.Path;
	PatternPath.ReplaceInline(TEXT("\\"), TEXT("/"));
	PatternPath.TrimStartAndEndInline();
	if (PatternPath.IsEmpty())
	{
		PatternPath = TEXT("Content/{ProjectName}");
	}
	FString ResolvedFolderPath = PatternPath;
	for (const TTuple<FString, FString>& Pair : Placeholders)
	{
		ResolvedFolderPath = ResolvedFolderPath.Replace(*Pair.Key, *Pair.Value, ESearchCase::CaseSensitive);
	}
	TMap<FString, FString> PlaceholdersWithBraces;
	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	if (Settings)
	{
		PlaceholdersWithBraces = Settings->GetPlaceholders();
		if (IsPathUnderExcluded(NormalizeRelativePath(ResolvedFolderPath), Settings->Exclusions, Placeholders))
		{
			return false;
		}
	}
	for (const TTuple<FString, FString>& Pair : Placeholders)
	{
		FString Key = Pair.Key;
		if (!Key.StartsWith(TEXT("{")))
		{
			Key = FString::Printf(TEXT("{%s}"), *Pair.Key);
		}
		PlaceholdersWithBraces.Add(Key, Pair.Value);
	}
	TArray<FString> ResolvedPaths = UConventionKeeperBlueprintLibrary::ResolveTemplatePaths(PatternPath, PlaceholdersWithBraces);
	if (ResolvedPaths.Num() == 0 && !PatternPath.Contains(TEXT("{")))
	{
		FString SinglePath = PatternPath;
		for (const TTuple<FString, FString>& Pair : PlaceholdersWithBraces)
		{
			SinglePath = SinglePath.Replace(*Pair.Key, *Pair.Value, ESearchCase::CaseSensitive);
		}
		SinglePath = NormalizeRelativePath(SinglePath);
		if (!SinglePath.IsEmpty())
		{
			ResolvedPaths.Add(SinglePath);
		}
	}
	return IsRelevantPath(ResolvedPaths, SelectedPaths);
}

TArray<FAssetNamingScopeEntry> UConventionKeeperRule_AssetNaming::GetScopesForValidation(const TArray<FString>& ResolvedPaths, const TArray<FString>& SelectedPaths)
{
	TArray<FAssetNamingScopeEntry> Result;
	TMap<FString, TPair<FString, TArray<FString>>> ScopeMap;

	auto AddOrMergeScope = [&ScopeMap](const FString& RulePath, const FString& QueryPath, TArray<FString> OnlyAssetPaths)
	{
		if (TPair<FString, TArray<FString>>* Existing = ScopeMap.Find(QueryPath))
		{
			if (OnlyAssetPaths.IsEmpty())
			{
				Existing->Value.Empty();
			}
			else if (!Existing->Value.IsEmpty())
			{
				for (const FString& A : OnlyAssetPaths)
				{
					Existing->Value.AddUnique(A);
				}
			}
		}
		else
		{
			ScopeMap.Add(QueryPath, TPair<FString, TArray<FString>>(RulePath, MoveTemp(OnlyAssetPaths)));
		}
	};

	for (const FString& ResolvedNorm : ResolvedPaths)
	{
		FString ResolvedPath = ResolvedNorm;
		if (ResolvedPath.EndsWith(TEXT("/")))
		{
			ResolvedPath.LeftChopInline(1);
		}
		if (!ResolvedPath.StartsWith(TEXT("Content/")))
		{
			ResolvedPath = FString(TEXT("Content/")) + ResolvedPath;
		}
		FString ResolvedNormSlash = ResolvedPath;
		if (!ResolvedNormSlash.EndsWith(TEXT("/")))
		{
			ResolvedNormSlash += TEXT("/");
		}

		if (SelectedPaths.IsEmpty())
		{
			AddOrMergeScope(ResolvedPath, ResolvedNormSlash, TArray<FString>());
			continue;
		}

		bool bAddedAny = false;
		for (const FString& S : SelectedPaths)
		{
			const FString NormS = AssetNamingPathHelpers::SelectedPathAsContentForm(S);
			const bool bSelectedIsFolder = S.EndsWith(TEXT("/"));
			if (bSelectedIsFolder)
			{
				if (NormS.StartsWith(ResolvedNormSlash))
				{
					AddOrMergeScope(ResolvedPath, NormS, TArray<FString>());
					bAddedAny = true;
				}
				else if (ResolvedNormSlash.StartsWith(NormS))
				{
					AddOrMergeScope(ResolvedPath, ResolvedNormSlash, TArray<FString>());
					bAddedAny = true;
				}
			}
			else
			{
				if (NormS.StartsWith(ResolvedNormSlash))
				{
					const FString AssetPathNoSlash = NormS.LeftChop(1);
					int32 LastSlash = INDEX_NONE;
					for (int32 i = AssetPathNoSlash.Len() - 1; i >= 0; --i)
					{
						if (AssetPathNoSlash[i] == TEXT('/'))
						{
							LastSlash = i;
							break;
						}
					}
					const FString ParentPath = LastSlash >= 0 ? AssetPathNoSlash.Left(LastSlash + 1) : ResolvedNormSlash;
					AddOrMergeScope(ResolvedPath, ParentPath, TArray<FString>{AssetPathNoSlash});
					bAddedAny = true;
				}
			}
		}
		if (!bAddedAny)
		{
			for (const FString& S : SelectedPaths)
			{
				const FString NormS = AssetNamingPathHelpers::SelectedPathAsContentForm(S);
				if (ResolvedNormSlash.StartsWith(NormS))
				{
					AddOrMergeScope(ResolvedPath, ResolvedNormSlash, TArray<FString>());
					break;
				}
			}
		}
	}

	for (const TTuple<FString, TPair<FString, TArray<FString>>>& Pair : ScopeMap)
	{
		FAssetNamingScopeEntry Entry;
		Entry.RulePath = Pair.Value.Key;
		Entry.QueryPath = Pair.Key;
		Entry.OnlyAssetPaths = Pair.Value.Value;
		Result.Add(Entry);
	}
	return Result;
}

void UConventionKeeperRule_AssetNaming::Validate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders)
{
	if (!CanValidate_Implementation(SelectedPaths, Placeholders))
	{
		return;
	}

	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	const bool bDebug = Settings && Settings->bDebug;
	const EMessageSeverity::Type FailureSeverity = ConventionKeeperRuleSeverityToMessageSeverity(Severity);

	FString PatternPath = FolderPathPattern.Path;
	PatternPath.ReplaceInline(TEXT("\\"), TEXT("/"));
	while (PatternPath.StartsWith(TEXT("/")))
	{
		PatternPath.RemoveFromStart(TEXT("/"));
	}
	if (PatternPath.IsEmpty())
	{
		PatternPath = TEXT("Content/{ProjectName}");
	}
	TMap<FString, FString> PlaceholdersWithBraces;
	if (Settings)
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
	for (const TTuple<FString, FString>& Pair : Placeholders)
	{
		FString Key = Pair.Key;
		if (!Key.StartsWith(TEXT("{")))
		{
			Key = FString::Printf(TEXT("{%s}"), *Pair.Key);
		}
		PlaceholdersWithBraces.Add(Key, Pair.Value);
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

	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();

	TArray<FString> PatternSegments;
	PatternPath.ParseIntoArray(PatternSegments, TEXT("/"), true);
	const int32 PatternSegmentCount = PatternSegments.Num();

	TArray<FString> ResolvedNormPaths;
	for (const FString& ResolvedPathWithSlash : ResolvedPaths)
	{
		FString ResolvedPath = ResolvedPathWithSlash;
		ResolvedPath.ReplaceInline(TEXT("\\"), TEXT("/"));
		if (ResolvedPath.StartsWith(TEXT("/"))) ResolvedPath.RemoveFromStart(TEXT("/"));
		if (!ResolvedPath.StartsWith(TEXT("Content/"))) ResolvedPath = FString(TEXT("Content/")) + ResolvedPath;
		TArray<FString> Segments;
		ResolvedPath.ParseIntoArray(Segments, TEXT("/"), true);
		if (Segments.Num() != PatternSegmentCount)
		{
			continue;
		}
		FString ResolvedNorm = NormalizeRelativePath(ResolvedPath);
		ResolvedNormPaths.Add(ResolvedNorm);
	}
	if (bDebug)
	{
		UE_LOG(LogTemp, Log, TEXT("[ConventionKeeper][AssetNaming] RuleId=%s PatternPath=%s ResolvedPaths=%d SelectedPaths=%d"),
			*RuleId.ToString(), *PatternPath, ResolvedNormPaths.Num(), SelectedPaths.Num());
		for (const FString& R : ResolvedNormPaths) { UE_LOG(LogTemp, Log, TEXT("  ResolvedNormPath: %s"), *R); }
		for (const FString& S : SelectedPaths) { UE_LOG(LogTemp, Log, TEXT("  SelectedPath: %s"), *S); }
	}
	TArray<FAssetNamingScopeEntry> ScopesToProcess = GetScopesForValidation(ResolvedNormPaths, SelectedPaths);
	if (bDebug)
	{
		UE_LOG(LogTemp, Log, TEXT("[ConventionKeeper][AssetNaming] ScopesToProcess=%d"), ScopesToProcess.Num());
		for (const FAssetNamingScopeEntry& Scope : ScopesToProcess)
		{
			UE_LOG(LogTemp, Log, TEXT("  Scope: RulePath=%s QueryPath=%s OnlyAssets=%d"),
				*Scope.RulePath, *Scope.QueryPath, Scope.OnlyAssetPaths.Num());
		}
	}

	for (const FAssetNamingScopeEntry& Scope : ScopesToProcess)
	{
		FString PackagePath = FString(TEXT("/Game/")) + Scope.QueryPath.Mid(8);
		PackagePath.ReplaceInline(TEXT("/"), TEXT("/"));
		if (PackagePath.EndsWith(TEXT("/")))
		{
			PackagePath.LeftChopInline(1);
		}

		TMap<FString, FString> PathPlaceholders;
		if (!ExtractPathPlaceholders(PatternPath, Scope.RulePath, PlaceholdersWithBraces, PathPlaceholders))
		{
			continue;
		}

		FString RequiredPrefix = NamingTemplate.IsEmpty()
			? (Prefix.IsEmpty() ? FString() : ResolveNamingTemplate(Prefix, PathPlaceholders))
			: ResolveNamingTemplate(NamingTemplate, PathPlaceholders);
		if (RequiredPrefix.IsEmpty())
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
		if (Filter.ClassPaths.IsEmpty())
		{
			continue;
		}

		TArray<FAssetData> AssetDataList;
		AssetRegistry.GetAssets(Filter, AssetDataList);

		const TSet<FString> OnlyAssetSet(Scope.OnlyAssetPaths);
		const bool bFilterToSpecificAssets = Scope.OnlyAssetPaths.Num() > 0;

		for (const FAssetData& AssetData : AssetDataList)
		{
			FString AssetName = AssetData.AssetName.ToString();
			FString PackageName = AssetData.PackageName.ToString();
			FString RelativePath = PackageName;
			if (RelativePath.StartsWith(TEXT("/Game/")))
			{
				RelativePath = FString(TEXT("Content/")) + RelativePath.Mid(6);
			}
			RelativePath.ReplaceInline(TEXT("/"), TEXT("/"));
			if (bFilterToSpecificAssets && !OnlyAssetSet.Contains(RelativePath))
			{
				continue;
			}
			if (Settings && IsPathUnderExcluded(RelativePath, Settings->Exclusions, PlaceholdersWithBraces))
			{
				continue;
			}

			bool bPrefixOk = RequiredPrefix.IsEmpty() || AssetName.StartsWith(RequiredPrefix);
			bool bSuffixOk = Suffix.IsEmpty() || AssetName.EndsWith(Suffix);
			bool bNumberOk = IsNumberSuffixValid(AssetName, NumberPaddingDigits);

			if (!bPrefixOk)
			{
				UConventionKeeperRule::LogRuleMessage(this, FailureSeverity,
					ConventionKeeperLoc::GetText(FName(TEXT("AssetNamingPrefix"))),
					&RelativePath, FText::Format(ConventionKeeperLoc::GetText(FName(TEXT("AssetNamingPrefixSuffix"))), FText::FromString(RequiredPrefix)));
			}
			else if (!bSuffixOk)
			{
				UConventionKeeperRule::LogRuleMessage(this, FailureSeverity,
					ConventionKeeperLoc::GetText(FName(TEXT("AssetNamingSuffix"))),
					&RelativePath, FText::Format(ConventionKeeperLoc::GetText(FName(TEXT("AssetNamingSuffixVal"))), FText::FromString(Suffix)));
			}
			else if (!bNumberOk)
			{
				FString Suggested = SuggestZeroPaddedName(AssetName, NumberPaddingDigits);
				UConventionKeeperRule::LogRuleMessage(this, FailureSeverity,
					FText::Format(ConventionKeeperLoc::GetText(FName(TEXT("AssetNamingNumber"))), FText::AsNumber(NumberPaddingDigits)),
					&RelativePath, FText::Format(ConventionKeeperLoc::GetText(FName(TEXT("AssetNamingSuggest"))), FText::FromString(Suggested)));
			}
			else if (bDebug)
			{
				UConventionKeeperRule::LogRuleMessage(this, EMessageSeverity::Info,
					ConventionKeeperLoc::GetText(FName(TEXT("AssetNamingOk"))),
					&RelativePath, FText());
			}
		}
	}
}

#if WITH_EDITOR
void UConventionKeeperRule_AssetNaming::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
