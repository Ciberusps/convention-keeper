// Pavel Penkov 2025 All Rights Reserved.

#include "Rules/ConventionKeeperRule_AssetPlacement.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"

#include "AssetRegistry/ARFilter.h"
#include "AssetRegistry/AssetRegistryHelpers.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "ConventionKeeperBlueprintLibrary.h"
#include "Development/ConventionKeeperSettings.h"
#include "Localization/ConventionKeeperLocalization.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "UObject/Class.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperRule_AssetPlacement)

bool UConventionKeeperRule_AssetPlacement::PathContainsSegment(const FString& NormalizedPath, const FString& Segment)
{
	if (Segment.IsEmpty())
	{
		return true;
	}
	FString Needle = TEXT("/") + Segment + TEXT("/");
	FString Path = NormalizedPath;
	Path.ReplaceInline(TEXT("\\"), TEXT("/"));
	if (!Path.EndsWith(TEXT("/")))
	{
		Path += TEXT("/");
	}
	return Path.Contains(Needle);
}

bool UConventionKeeperRule_AssetPlacement::CanValidate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const
{
	FString PatternPath = FolderPathPattern.Path;
	PatternPath.ReplaceInline(TEXT("\\"), TEXT("/"));
	PatternPath.TrimStartAndEndInline();
	if (PatternPath.IsEmpty())
	{
		PatternPath = TEXT("Content/{ProjectName}");
	}
	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	TMap<FString, FString> PlaceholdersWithBraces;
	if (Settings)
	{
		PlaceholdersWithBraces = Settings->GetPlaceholders();
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
	FString ResolvedFolderPath = PatternPath;
	for (const TTuple<FString, FString>& Pair : PlaceholdersWithBraces)
	{
		ResolvedFolderPath = ResolvedFolderPath.Replace(*Pair.Key, *Pair.Value, ESearchCase::CaseSensitive);
	}
	if (Settings && UConventionKeeperRule_AssetNaming::IsPathUnderExcluded(UConventionKeeperRule::NormalizeRelativePath(ResolvedFolderPath), Settings->Exclusions, PlaceholdersWithBraces))
	{
		return false;
	}
	TArray<FString> ResolvedPaths = UConventionKeeperBlueprintLibrary::ResolveTemplatePaths(PatternPath, PlaceholdersWithBraces);
	if (ResolvedPaths.Num() == 0 && !PatternPath.Contains(TEXT("{")))
	{
		FString SinglePath = PatternPath;
		for (const TTuple<FString, FString>& Pair : PlaceholdersWithBraces)
		{
			SinglePath = SinglePath.Replace(*Pair.Key, *Pair.Value, ESearchCase::CaseSensitive);
		}
		SinglePath = UConventionKeeperRule::NormalizeRelativePath(SinglePath);
		if (!SinglePath.IsEmpty())
		{
			ResolvedPaths.Add(SinglePath);
		}
	}
	return UConventionKeeperRule_AssetNaming::IsRelevantPath(ResolvedPaths, SelectedPaths);
}

void UConventionKeeperRule_AssetPlacement::Validate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders)
{
	if (!CanValidate_Implementation(SelectedPaths, Placeholders))
	{
		return;
	}

	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
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

	TArray<FString> PatternSegments;
	PatternPath.ParseIntoArray(PatternSegments, TEXT("/"), true);
	const int32 PatternSegmentCount = PatternSegments.Num();

	TArray<FString> ResolvedNormPaths;
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
		ResolvedNormPaths.Add(UConventionKeeperRule::NormalizeRelativePath(ResolvedPath));
	}

	TArray<FAssetNamingScopeEntry> ScopesToProcess = UConventionKeeperRule_AssetNaming::GetScopesForValidation(ResolvedNormPaths, SelectedPaths);
	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();

	for (const FAssetNamingScopeEntry& Scope : ScopesToProcess)
	{
		FString PackagePath = FString(TEXT("/Game/")) + Scope.QueryPath.Mid(8);
		PackagePath.ReplaceInline(TEXT("\\"), TEXT("/"));
		if (PackagePath.EndsWith(TEXT("/")))
		{
			PackagePath.LeftChopInline(1);
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
			if (UClass* LoadedClass = UClass::TryFindTypeSlow<UClass>(*ClassPath, EFindFirstObjectOptions::ExactClass))
			{
				Filter.ClassPaths.Add(FTopLevelAssetPath(LoadedClass));
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
			FString PackageName = AssetData.PackageName.ToString();
			FString RelativePath = PackageName;
			if (RelativePath.StartsWith(TEXT("/Game/")))
			{
				RelativePath = FString(TEXT("Content/")) + RelativePath.Mid(6);
			}
			RelativePath.ReplaceInline(TEXT("\\"), TEXT("/"));
			if (bFilterToSpecificAssets && !OnlyAssetSet.Contains(RelativePath))
			{
				continue;
			}
			if (Settings && UConventionKeeperRule_AssetNaming::IsPathUnderExcluded(RelativePath, Settings->Exclusions, PlaceholdersWithBraces))
			{
				continue;
			}
			if (!ShouldValidateAsset(AssetData))
			{
				continue;
			}

			FString NormalizedPath = RelativePath;
			if (!NormalizedPath.EndsWith(TEXT("/")))
			{
				NormalizedPath += TEXT("/");
			}
			if (!PathContainsSegment(NormalizedPath, RequiredPathSegment))
			{
				UConventionKeeperRule::LogRuleMessage(this, FailureSeverity,
					ConventionKeeperLoc::GetText(FName(TEXT("AssetPlacementMustBeInFolder"))),
					&RelativePath,
					FText::Format(ConventionKeeperLoc::GetText(FName(TEXT("AssetPlacementMustBeInFolderSuffix"))), FText::FromString(RequiredPathSegment)));
			}
		}
	}
}
