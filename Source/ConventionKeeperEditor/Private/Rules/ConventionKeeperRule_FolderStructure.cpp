// Pavel Penkov 2025 All Rights Reserved.

#include "Rules/ConventionKeeperRule_FolderStructure.h"

#include "ConventionKeeperBlueprintLibrary.h"
#include "ConventionKeeperConvention_Base.h"
#include "Development/ConventionKeeperSettings.h"
#include "Localization/ConventionKeeperLocalization.h"
#include "Misc/Paths.h"
#include "Rules/ConventionKeeperRule.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperRule_FolderStructure)

FString UConventionKeeperRule_FolderStructure::ResolvePlaceholdersForPath(const FString& DirectoryPath, const TMap<FString, FString>& Placeholders)
{
	FString ResultPath = DirectoryPath;
	for (const TTuple<FString, FString>& Placeholder : Placeholders)
	{
		ResultPath = ResultPath.Replace(*Placeholder.Key, *Placeholder.Value, ESearchCase::CaseSensitive);
	}
	return ResultPath;
}

FString UConventionKeeperRule_FolderStructure::GetRequiredFolderProjectRelative(
	const FString& ResolvedBasePath,
	const FString& RequiredFolderPath,
	const TMap<FString, FString>& MergedPlaceholders)
{
	FString R = ResolvePlaceholdersForPath(RequiredFolderPath, MergedPlaceholders);
	R.ReplaceInline(TEXT("\\"), TEXT("/"));
	R.TrimStartAndEndInline();
	while (R.StartsWith(TEXT("/")))
	{
		R.RemoveFromStart(TEXT("/"));
	}
	if (R.StartsWith(TEXT("Content/"), ESearchCase::IgnoreCase))
	{
		return R;
	}
	return UConventionKeeperRule::NormalizeRelativePath(ResolvedBasePath) + R;
}

FString UConventionKeeperRule_FolderStructure::GetAbsolutePathForRequiredSubfolder(
	const FString& ResolvedBasePath,
	const FString& RequiredFolderPath,
	const TMap<FString, FString>& MergedPlaceholders)
{
	FString R = ResolvePlaceholdersForPath(RequiredFolderPath, MergedPlaceholders);
	R.ReplaceInline(TEXT("\\"), TEXT("/"));
	R.TrimStartAndEndInline();
	while (R.StartsWith(TEXT("/")))
	{
		R.RemoveFromStart(TEXT("/"));
	}
	const FString ProjectDir = FPaths::ProjectDir();
	if (R.StartsWith(TEXT("Content/"), ESearchCase::IgnoreCase))
	{
		return FPaths::ConvertRelativePathToFull(ProjectDir / R);
	}
	return FPaths::ConvertRelativePathToFull(ProjectDir / ResolvedBasePath / R);
}

namespace FolderStructurePathHelpers
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

bool UConventionKeeperRule_FolderStructure::IsRelevantPath(const FString& ResolvedPath, const TArray<FString>& SelectedPaths)
{
	return IsRelevantPath(TArray<FString>{UConventionKeeperRule::NormalizeRelativePath(ResolvedPath)}, SelectedPaths);
}

bool UConventionKeeperRule_FolderStructure::IsRelevantPath(const TArray<FString>& ResolvedPathsToCheck, const TArray<FString>& SelectedPaths)
{
	if (SelectedPaths.IsEmpty())
	{
		return true;
	}
	for (const FString& ResolvedPath : ResolvedPathsToCheck)
	{
		const FString NormalizedResolvedPath = UConventionKeeperRule::NormalizeRelativePath(ResolvedPath);
		for (const FString& SelectedPath : SelectedPaths)
		{
			const FString NormalizedSelectedPath = FolderStructurePathHelpers::SelectedPathAsContentForm(SelectedPath);
			if (NormalizedResolvedPath.StartsWith(NormalizedSelectedPath))
			{
				return true;
			}
		}
	}
	return false;
}

bool UConventionKeeperRule_FolderStructure::IsPathUnderExcluded(const FString& ResolvedPath, const TArray<FString>& Exclusions, const TMap<FString, FString>& Placeholders)
{
	const FString NormalizedPath = UConventionKeeperRule::NormalizeRelativePath(ResolvedPath);
	for (const FString& Exclusion : Exclusions)
	{
		const FString ResolvedExclude = ResolvePlaceholdersForPath(Exclusion, Placeholders);
		FString NormalizedExclude = ResolvedExclude;
		NormalizedExclude.ReplaceInline(TEXT("\\"), TEXT("/"));
		NormalizedExclude.TrimStartAndEndInline();
		const bool bExclusionIsFolder = NormalizedExclude.EndsWith(TEXT("/"));
		if (bExclusionIsFolder)
		{
			NormalizedExclude = UConventionKeeperRule::NormalizeRelativePath(ResolvedExclude);
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

bool UConventionKeeperRule_FolderStructure::DoesDirectoryExist(const FString& DirectoryPath, const TMap<FString, FString>& Placeholders)
{
	FString ResultPath = DirectoryPath;
	for (const TTuple<FString, FString>& Placeholder : Placeholders)
	{
		ResultPath = ResultPath.Replace(*Placeholder.Key, *Placeholder.Value, ESearchCase::CaseSensitive);
	}

	const FString AbsolutePath = FPaths::ProjectDir() / ResultPath;
	return FPaths::DirectoryExists(AbsolutePath);
}

bool UConventionKeeperRule_FolderStructure::CanValidate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const
{
	const FString ResolvedFolderPath = ResolvePlaceholdersForPath(FolderPath.Path, Placeholders);

	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	if (Settings && IsPathUnderExcluded(ResolvedFolderPath, Settings->Exclusions, Placeholders))
	{
		return false;
	}

	TArray<FString> PathsToCheck;
	if (ResolvedFolderPath.Contains(TEXT("{")))
	{
		TMap<FString, FString> PlaceholdersWithBraces = Settings ? Settings->GetPlaceholders() : TMap<FString, FString>();
		for (const TTuple<FString, FString>& P : Placeholders)
		{
			FString Key = P.Key;
			if (!Key.StartsWith(TEXT("{")))
			{
				Key = FString::Printf(TEXT("{%s}"), *P.Key);
			}
			PlaceholdersWithBraces.Add(Key, P.Value);
		}
		TArray<FString> Resolved = UConventionKeeperBlueprintLibrary::ResolveTemplatePaths(ResolvedFolderPath, PlaceholdersWithBraces);
		for (FString& P : Resolved)
		{
			P.ReplaceInline(TEXT("\\"), TEXT("/"));
			if (P.StartsWith(TEXT("/")))
			{
				P.RemoveFromStart(TEXT("/"));
			}
			PathsToCheck.Add(UConventionKeeperRule::NormalizeRelativePath(P));
		}
	}
	else
	{
		PathsToCheck.Add(UConventionKeeperRule::NormalizeRelativePath(ResolvedFolderPath));
	}
	return IsRelevantPath(PathsToCheck, SelectedPaths);
}

TArray<FString> UConventionKeeperRule_FolderStructure::GetConcreteBasePathsForFolderRule(
	const FString& FolderPathPath,
	const TMap<FString, FString>& Placeholders,
	const UConventionKeeperSettings* Settings,
	const TArray<FString>& SelectedPaths)
{
	const FString ResolvedFolderPath = ResolvePlaceholdersForPath(FolderPathPath, Placeholders);
	TArray<FString> PathsToCheck;
	if (ResolvedFolderPath.Contains(TEXT("{")))
	{
		TMap<FString, FString> PlaceholdersWithBraces = Settings ? Settings->GetPlaceholders() : TMap<FString, FString>();
		for (const TTuple<FString, FString>& P : Placeholders)
		{
			FString Key = P.Key;
			if (!Key.StartsWith(TEXT("{")))
			{
				Key = FString::Printf(TEXT("{%s}"), *P.Key);
			}
			PlaceholdersWithBraces.Add(Key, P.Value);
		}
		TArray<FString> Resolved = UConventionKeeperBlueprintLibrary::ResolveTemplatePaths(ResolvedFolderPath, PlaceholdersWithBraces);
		for (FString& P : Resolved)
		{
			P.ReplaceInline(TEXT("\\"), TEXT("/"));
			if (P.StartsWith(TEXT("/")))
			{
				P.RemoveFromStart(TEXT("/"));
			}
			PathsToCheck.Add(UConventionKeeperRule::NormalizeRelativePath(P));
		}
	}
	else
	{
		PathsToCheck.Add(UConventionKeeperRule::NormalizeRelativePath(ResolvedFolderPath));
	}
	if (SelectedPaths.IsEmpty())
	{
		return PathsToCheck;
	}
	TArray<FString> Filtered;
	for (const FString& BasePath : PathsToCheck)
	{
		for (const FString& SelectedPath : SelectedPaths)
		{
			const FString NormalizedSelectedPath = FolderStructurePathHelpers::SelectedPathAsContentForm(SelectedPath);
			if (BasePath.StartsWith(NormalizedSelectedPath))
			{
				Filtered.AddUnique(BasePath);
				break;
			}
			if (NormalizedSelectedPath.StartsWith(BasePath))
			{
				Filtered.AddUnique(NormalizedSelectedPath);
				break;
			}
		}
	}
	return Filtered;
}

void UConventionKeeperRule_FolderStructure::Validate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders)
{
	if (!CanValidate_Implementation(SelectedPaths, Placeholders))
	{
		return;
	}

	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	const bool bDebug = Settings && Settings->bDebug;
	const EMessageSeverity::Type FailureSeverity = ConventionKeeperRuleSeverityToMessageSeverity(Severity);

	const FString ResolvedFolderPath = ResolvePlaceholdersForPath(FolderPath.Path, Placeholders);
	TArray<FString> BasePathsToValidate = GetConcreteBasePathsForFolderRule(FolderPath.Path, Placeholders, Settings, SelectedPaths);
	if (BasePathsToValidate.IsEmpty())
	{
		return;
	}

	TMap<FString, FString> PlaceholdersWithBraces = Settings ? Settings->GetPlaceholders() : TMap<FString, FString>();
	for (const TTuple<FString, FString>& P : Placeholders)
	{
		FString Key = P.Key;
		if (!Key.StartsWith(TEXT("{")))
		{
			Key = FString::Printf(TEXT("{%s}"), *P.Key);
		}
		PlaceholdersWithBraces.Add(Key, P.Value);
	}

	for (const FString& ResolvedBasePath : BasePathsToValidate)
	{
		const FString AbsoluteBasePath = FPaths::ProjectDir() / ResolvedBasePath;
		const bool bExists = FPaths::DirectoryExists(AbsoluteBasePath);
		if (!bExists)
		{
			UConventionKeeperRule::LogRuleMessage(this, FailureSeverity,
				ConventionKeeperLoc::GetText(FName(TEXT("FolderMissing"))),
				&ResolvedBasePath);
			continue;
		}
		if (bDebug)
		{
			UConventionKeeperRule::LogRuleMessage(this, EMessageSeverity::Info,
				ConventionKeeperLoc::GetText(FName(TEXT("FolderExists"))),
				&ResolvedBasePath, ConventionKeeperLoc::GetText(FName(TEXT("FolderOkSuffix"))));
		}

		TMap<FString, FString> PathPlaceholders;
		if (ResolvedFolderPath.Contains(TEXT("{")))
		{
			UConventionKeeperBlueprintLibrary::ExtractPathPlaceholders(ResolvedFolderPath, ResolvedBasePath, PlaceholdersWithBraces, PathPlaceholders);
		}
		TMap<FString, FString> MergedPlaceholders = PlaceholdersWithBraces;
		for (const TTuple<FString, FString>& PP : PathPlaceholders)
		{
			MergedPlaceholders.Add(FString::Printf(TEXT("{%s}"), *PP.Key), PP.Value);
		}

		for (const FDirectoryPath& RequiredFolder : RequiredFolders)
		{
			const FString AbsoluteRequired = GetAbsolutePathForRequiredSubfolder(ResolvedBasePath, RequiredFolder.Path, MergedPlaceholders);
			const FString ResolvedRequiredForLog = ResolvePlaceholdersForPath(RequiredFolder.Path, MergedPlaceholders);
			const bool bRequiredExists = FPaths::DirectoryExists(AbsoluteRequired);
			if (!bRequiredExists)
			{
				UConventionKeeperRule::LogRuleMessage(this, FailureSeverity,
					ConventionKeeperLoc::GetText(FName(TEXT("RequiredSubfolderMissing"))),
					&ResolvedRequiredForLog, FText::Format(ConventionKeeperLoc::GetText(FName(TEXT("RequiredSubfolderMissingSuffix"))), FText::FromString(ResolvedBasePath)));
			}
			else if (bDebug)
			{
				UConventionKeeperRule::LogRuleMessage(this, EMessageSeverity::Info,
					ConventionKeeperLoc::GetText(FName(TEXT("RequiredSubfolderExists"))),
					&ResolvedRequiredForLog, ConventionKeeperLoc::GetText(FName(TEXT("FolderOkSuffix"))));
			}
		}

		if (bOtherFoldersNotAllowed)
		{
			TArray<FString> AllFoldersInThisPath;
			UConventionKeeperBlueprintLibrary::GetDiskFoldersRelativeToRoot(ResolvedBasePath, AllFoldersInThisPath);

			for (const FString& Folder : AllFoldersInThisPath)
			{
				if (Settings && IsPathUnderExcluded(Folder, Settings->Exclusions, Placeholders))
				{
					continue;
				}

				const FString DiskNorm = UConventionKeeperRule::NormalizeRelativePath(Folder);
				bool bFolderAllowed = false;
				for (const FDirectoryPath& RequiredFolder : RequiredFolders)
				{
					const FString RequiredProjectRelative = GetRequiredFolderProjectRelative(ResolvedBasePath, RequiredFolder.Path, MergedPlaceholders);
					const FString RequiredNorm = UConventionKeeperRule::NormalizeRelativePath(RequiredProjectRelative);
					if (DiskNorm.Equals(RequiredNorm, ESearchCase::IgnoreCase))
					{
						bFolderAllowed = true;
						break;
					}
				}

				if (!bFolderAllowed)
				{
					UConventionKeeperRule::LogRuleMessage(this, FailureSeverity,
						ConventionKeeperLoc::GetText(FName(TEXT("DisallowedFolder"))),
						&ResolvedBasePath, FText::Format(ConventionKeeperLoc::GetText(FName(TEXT("DisallowedFolderSuffix"))), FText::FromString(Folder)));
				}
			}

			if (bDebug && AllFoldersInThisPath.Num() == 0)
			{
				UConventionKeeperRule::LogRuleMessage(this, EMessageSeverity::Info,
					ConventionKeeperLoc::GetText(FName(TEXT("NoExtraFolders"))),
					&ResolvedBasePath, ConventionKeeperLoc::GetText(FName(TEXT("FolderOkSuffix"))));
			}
		}
	}
}

#if WITH_EDITOR
void UConventionKeeperRule_FolderStructure::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	ConvertAllPathsToRelativePaths();
}
#endif

void UConventionKeeperRule_FolderStructure::ConvertAllPathsToRelativePaths()
{
	UConventionKeeperBlueprintLibrary::MakePathRelativeToProjectDir(FolderPath.Path);

	for (FDirectoryPath& Dir : RequiredFolders)
	{
		UConventionKeeperBlueprintLibrary::MakePathRelativeToProjectDir(Dir.Path);
	}
}
