// Pavel Penkov 2025 All Rights Reserved.

#include "Commandlets/ConventionKeeperCommandlet.h"
#include "ConventionCoverage.h"
#include "ConventionKeeperConvention_Base.h"
#include "ConventionKeeperValidationHooks.h"
#include "ConventionKeeperValidationContext.h"
#include "Development/ConventionKeeperSettings.h"
#include "Localization/ConventionKeeperLocalization.h"
#include "Logging/MessageLog.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Framework/Application/SlateApplication.h"
#include "Misc/MessageDialog.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "Misc/ScopedSlowTask.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperCommandlet)

#define LOCTEXT_NAMESPACE "ConventionKeeperCommandlet"

static int32 CountAssetsInValidationScope(TArrayView<const FString> RelativePaths, bool bAssetPaths)
{
	if (bAssetPaths)
	{
		return RelativePaths.Num();
	}

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	if (RelativePaths.IsEmpty())
	{
		FARFilter Filter;
		Filter.PackagePaths.Add(TEXT("/Game"));
		Filter.bRecursivePaths = true;
		TArray<FAssetData> Assets;
		AssetRegistry.GetAssets(Filter, Assets);
		return Assets.Num();
	}

	TSet<FName> UniquePackages;
	for (const FString& RelPath : RelativePaths)
	{
		FString RelCopy = RelPath;
		RelCopy.ReplaceInline(TEXT("\\"), TEXT("/"));
		if (RelCopy.EndsWith(TEXT("/")))
		{
			RelCopy.LeftChopInline(1);
		}
		FString LongPackage = TEXT("/Game/");
		if (RelCopy.StartsWith(TEXT("Content/"), ESearchCase::IgnoreCase))
		{
			LongPackage += RelCopy.Mid(8);
		}
		else
		{
			LongPackage += RelCopy;
		}

		FARFilter Filter;
		Filter.PackagePaths.Add(*LongPackage);
		Filter.bRecursivePaths = true;
		TArray<FAssetData> Assets;
		AssetRegistry.GetAssets(Filter, Assets);
		for (const FAssetData& AssetEntry : Assets)
		{
			UniquePackages.Add(AssetEntry.PackageName);
		}
	}
	return UniquePackages.Num();
}

UConventionKeeperCommandlet::UConventionKeeperCommandlet()
{
	IsClient = false;
	IsEditor = true;
	IsServer = false;
	LogToConsole = true;
	ShowErrorCount = true;
}

static FString NormalizeRelativePathForValidation(const FString& InPath)
{
	FString Result = InPath;
	Result.ReplaceInline(TEXT("\\"), TEXT("/"));
	Result.TrimStartAndEndInline();
	while (Result.StartsWith(TEXT("/")))
	{
		Result.RemoveFromStart(TEXT("/"));
	}
	if (Result.StartsWith(TEXT("All/")))
	{
		Result.RemoveFromStart(TEXT("All/"));
	}
	if (Result.StartsWith(TEXT("Game/")))
	{
		Result = FString(TEXT("Content/")) + Result.Mid(5);
	}
	if (!Result.EndsWith(TEXT("/")))
	{
		Result += TEXT("/");
	}
	return Result;
}

FString UConventionKeeperCommandlet::ConvertPathToRelativeForValidation(const FString& InPath)
{
	FString Path = InPath;
	Path.TrimStartAndEndInline();
	Path.ReplaceInline(TEXT("\\"), TEXT("/"));

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

	const int32 DotPos = Path.Find(TEXT("."), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	if (DotPos != INDEX_NONE)
	{
		const FString Ext = Path.Mid(DotPos + 1).ToLower();
		if (Ext == TEXT("uasset") || Ext == TEXT("umap"))
		{
			Path = Path.Left(DotPos);
		}
		else
		{
			// Content Browser and logs may provide object path "/Game/Folder/Asset.Asset".
			// For validation/exclusions we normalize to package path "/Game/Folder/Asset".
			const int32 LastSlashPos = Path.Find(TEXT("/"), ESearchCase::CaseSensitive, ESearchDir::FromEnd);
			if (LastSlashPos != INDEX_NONE && DotPos > LastSlashPos)
			{
				const FString PackageLeaf = Path.Mid(LastSlashPos + 1, DotPos - LastSlashPos - 1);
				const FString ObjectName = Path.Mid(DotPos + 1);
				if (!PackageLeaf.IsEmpty() && ObjectName == PackageLeaf)
				{
					Path = Path.Left(DotPos);
				}
			}
		}
	}

	if (Path.StartsWith(TEXT("Content/")))
	{
		return NormalizeRelativePathForValidation(Path);
	}

	if (Path.StartsWith(TEXT("Game/")))
	{
		return NormalizeRelativePathForValidation(FString(TEXT("Content/")) + Path.Mid(5));
	}

	FString ForPackageName = Path;
	if (!ForPackageName.StartsWith(TEXT("Game")))
	{
		ForPackageName = FString(TEXT("Game/")) + ForPackageName;
	}
	if (FPackageName::IsValidLongPackageName(ForPackageName))
	{
		FString Filename = FPackageName::LongPackageNameToFilename(ForPackageName, TEXT(""));
		FPaths::MakePathRelativeTo(Filename, *FPaths::ProjectDir());
		return NormalizeRelativePathForValidation(Filename);
	}

	return NormalizeRelativePathForValidation(FString(TEXT("Content/")) + Path);
}

FString UConventionKeeperCommandlet::ConvertPathToRelativeForExclusion(const FString& InPath, bool bFolder)
{
	FString Result = ConvertPathToRelativeForValidation(InPath);
	if (!bFolder && Result.EndsWith(TEXT("/")))
	{
		Result.LeftChopInline(1);
	}
	return Result;
}

bool UConventionKeeperCommandlet::ValidateData(TArrayView<const FString> Paths, bool bAssetPaths)
{
	const UConventionKeeperSettings* ConventionKeeperSettings = GetDefault<UConventionKeeperSettings>();
	if (ConventionKeeperSettings && !ConventionKeeperSettings->GetEffectiveValidationEnabled())
	{
		FText Msg = ConventionKeeperLoc::GetText(FName(TEXT("ValidationDisabled")));
		if (IsRunningCommandlet())
		{
			UE_LOG(LogTemp, Warning, TEXT("ConventionKeeper: %s"), *Msg.ToString());
		}
		else
		{
			FMessageLog(TEXT("ConventionKeeper")).Info(Msg);
			FMessageLog(TEXT("ConventionKeeper")).Open(EMessageSeverity::Info, true);
		}
		return true;
	}
	UConventionKeeperConvention_Base* Convention = ConventionKeeperSettings ? ConventionKeeperSettings->GetResolvedConvention() : nullptr;
	if (!Convention)
	{
		UE_LOG(LogTemp, Error, TEXT("ConventionKeeper: Settings or Convention/Convention Asset is not set."));
		return false;
	}

	TArray<FString> RelativePaths;
	RelativePaths.Reserve(Paths.Num());
	for (const FString& Path : Paths)
	{
		RelativePaths.Add(bAssetPaths
			? UConventionKeeperCommandlet::ConvertPathToRelativeForExclusion(Path, false)
			: UConventionKeeperCommandlet::ConvertPathToRelativeForValidation(Path));
	}

#if WITH_EDITOR
	const bool bInteractiveUI = !IsRunningCommandlet() && FSlateApplication::IsInitialized();
#else
	const bool bInteractiveUI = false;
#endif

	int32 EstimatedAssetsInScope = 0;
	if (bInteractiveUI)
	{
		EstimatedAssetsInScope = CountAssetsInValidationScope(RelativePaths, bAssetPaths);
	}

	const int32 LargeThreshold =
		(bInteractiveUI && ConventionKeeperSettings) ? ConventionKeeperSettings->LargeValidationConfirmThreshold : 0;
	const bool bLargeInteractiveScope =
		bInteractiveUI && LargeThreshold > 0 && EstimatedAssetsInScope > LargeThreshold;

	if (ConventionKeeperSettings && bLargeInteractiveScope)
	{
		const FText Title = LOCTEXT("LargeValidationTitle", "Convention Keeper");
		const FText Body = FText::Format(
			LOCTEXT(
				"LargeValidationBody",
				"About {0} assets are in scope for this validation. Run convention checks? This may take a while."),
			FText::AsNumber(EstimatedAssetsInScope));
		if (FMessageDialog::Open(EAppMsgType::YesNo, Body, Title) != EAppReturnType::Yes)
		{
			return true;
		}
	}

#if WITH_EDITOR
	const FConventionKeeperAssetValidationScope PerAssetValidationScope(bAssetPaths);
#endif
	if (ConventionKeeperSettings && bLargeInteractiveScope)
	{
		const TArray<UConventionKeeperRule*> RulesForProgress = Convention->GetEffectiveRules();
		const float TotalRules = static_cast<float>(FMath::Max(1, RulesForProgress.Num()));
		FScopedSlowTask SlowTask(TotalRules, LOCTEXT("SlowValidate", "Convention Keeper: validating..."));
		SlowTask.MakeDialog(true);

		FConventionKeeperValidationHooks Hooks;
		Hooks.ShouldAbort = [&SlowTask]() { return SlowTask.ShouldCancel(); };
		UConventionKeeperConvention_Base* ConventionForDescription = Convention;
		Hooks.OnRuleProgress = [&SlowTask, ConventionForDescription](int32 Idx, int32 Total, UConventionKeeperRule* Rule)
		{
			const FText Line = Rule
				? FText::Format(
					LOCTEXT("RuleProgressFmt", "{0} / {1} — {2}"),
					FText::AsNumber(Idx + 1),
					FText::AsNumber(Total),
					Rule->GetDisplayDescription(ConventionForDescription))
				: FText::Format(
					LOCTEXT("RuleProgressNoRule", "{0} / {1}"),
					FText::AsNumber(Idx + 1),
					FText::AsNumber(Total));
			SlowTask.EnterProgressFrame(1.f, Line);
		};
		Convention->ValidateFolderStructuresForPathsInternal(RelativePaths, &Hooks);
	}
	else
	{
		Convention->ValidateFolderStructuresForPathsInternal(RelativePaths, nullptr);
	}
	return true;
}

#undef LOCTEXT_NAMESPACE

int32 UConventionKeeperCommandlet::Main(const FString& Params)
{
	const bool bCoverage = FParse::Param(*Params, TEXT("Coverage"));
	const bool bCompliance = FParse::Param(*Params, TEXT("Compliance"));
	int32 MinCoverage = 0;
	int32 MinCompliance = 0;
	FParse::Value(*Params, TEXT("MinCoverage="), MinCoverage);
	FParse::Value(*Params, TEXT("MinCompliance="), MinCompliance);

	if (bCoverage || bCompliance)
	{
		const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
		UConventionKeeperConvention_Base* Convention = Settings ? Settings->GetResolvedConvention() : nullptr;
		if (!Settings || !Convention)
		{
			UE_LOG(LogTemp, Error, TEXT("ConventionKeeper: Convention not set. Set in Project Settings."));
			return 1;
		}
		FConventionCoverageResult Result = ConventionCoverage::RunAnalysis(Convention, Settings, TArray<FString>());
		const int32 CoveragePct = Result.TotalAssets > 0 ? FMath::RoundToInt(100.0 * Result.CoveredAssets / Result.TotalAssets) : 0;
		const int32 CompliancePct = Result.CoveredAssets > 0 ? FMath::RoundToInt(100.0 * Result.CompliantAssets / Result.CoveredAssets) : 0;
		if (bCoverage)
		{
			UE_LOG(LogTemp, Log, TEXT("ConventionKeeper: In rule scope: %d%% (%d/%d assets in a path where a rule applies)."), CoveragePct, Result.CoveredAssets, Result.TotalAssets);
		}
		if (bCompliance)
		{
			UE_LOG(LogTemp, Log, TEXT("ConventionKeeper: Compliance: of those in scope, %d%% (%d/%d pass)."), CompliancePct, Result.CompliantAssets, Result.CoveredAssets);
		}
		for (const FConventionCoverageClassStats& Stats : Result.PerClass)
		{
			if (bCoverage && Stats.Covered == 0 && Stats.Total > 0)
			{
				UE_LOG(LogTemp, Log, TEXT("  %s: %d assets, no rule"), *Stats.ClassName, Stats.Total);
			}
			else if (bCoverage && Stats.Covered > 0)
			{
				const int32 CvPct = Stats.Total > 0 ? static_cast<int32>(FMath::RoundToInt(100.0 * Stats.Covered / Stats.Total)) : 0;
				UE_LOG(LogTemp, Log, TEXT("  %s: %d total; %d in scope (%d%%)"), *Stats.ClassName, Stats.Total, Stats.Covered, CvPct);
			}
			if (bCompliance && Stats.Covered > 0)
			{
				const int32 Cp = static_cast<int32>(FMath::RoundToInt(100.0 * Stats.Compliant / Stats.Covered));
				UE_LOG(LogTemp, Log, TEXT("  %s: %d in scope; %d%% compliant (%d/%d)"), *Stats.ClassName, Stats.Covered, Cp, Stats.Compliant, Stats.Covered);
			}
		}
		const int32 CoverageThreshold = (MinCoverage > 0) ? MinCoverage : (Settings->MinCoveragePercent);
		if (bCoverage && CoverageThreshold > 0 && Result.TotalAssets > 0 && CoveragePct < CoverageThreshold)
		{
			UE_LOG(LogTemp, Error, TEXT("ConventionKeeper: Coverage %d%% is below minimum %d%%. Failing."), CoveragePct, CoverageThreshold);
			return 1;
		}
		const int32 ComplianceThreshold = (MinCompliance > 0) ? MinCompliance : (Settings->MinCompliancePercent);
		if (bCompliance && ComplianceThreshold > 0 && Result.CoveredAssets > 0 && CompliancePct < ComplianceThreshold)
		{
			UE_LOG(LogTemp, Error, TEXT("ConventionKeeper: Compliance %d%% is below minimum %d%%. Failing."), CompliancePct, ComplianceThreshold);
			return 1;
		}
		return 0;
	}

	TArray<FString> Paths;
	FString PathsValue;
	if (FParse::Value(*Params, TEXT("Paths="), PathsValue))
	{
		PathsValue.ParseIntoArray(Paths, TEXT(";"), true);
	}
	const bool bAssetPaths = FParse::Param(*Params, TEXT("AssetPaths"));

	const bool bSuccess = ValidateData(Paths, bAssetPaths);
	return bSuccess ? 0 : 1;
}
