// Pavel Penkov 2025 All Rights Reserved.


#include "ConventionKeeperConvention.h"

#include "Development/ConventionKeeperSettings.h"

#define LOCTEXT_NAMESPACE "FConventionKeeperEditorModule"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperConvention)

void UConventionKeeperConvention::ValidateFolderStructures_Implementation()
{
	const UConventionKeeperSettings* ConventionKeeperSettings = GetDefault<UConventionKeeperSettings>();
	TMap<FString, FString> Placeholders = ConventionKeeperSettings->GetPlaceholders();

	const TArray<FString> EmptyPaths;
	for (UConventionRule* Rule : Rules)
	{
		if (!Rule)
		{
			continue;
		}

		if (Rule->CanValidate(EmptyPaths, Placeholders))
		{
			Rule->Validate(EmptyPaths, Placeholders);
		}
	}
}

void UConventionKeeperConvention::ValidateFolderStructuresForPaths(const TArray<FString>& SelectedPaths)
{
	const UConventionKeeperSettings* ConventionKeeperSettings = GetDefault<UConventionKeeperSettings>();
	TMap<FString, FString> Placeholders = ConventionKeeperSettings->GetPlaceholders();

	for (UConventionRule* Rule : Rules)
	{
		if (!Rule)
		{
			continue;
		}

		if (Rule->CanValidate(SelectedPaths, Placeholders))
		{
			Rule->Validate(SelectedPaths, Placeholders);
		}
	}
}

bool UConventionKeeperConvention::DoesDirectoryExist(const FString& DirectoryPath, const TMap<FString, FString>& Placeholders)
{
	FString ResultPath = DirectoryPath;
	for (TTuple<FString, FString> Placeholder : Placeholders)
	{
		ResultPath = ResultPath.Replace(*Placeholder.Key, *Placeholder.Value, ESearchCase::CaseSensitive);
	}

	FString AbsolutePath = FPaths::ProjectDir() / ResultPath;
	return FPaths::DirectoryExists(AbsolutePath);
}

// TArray<FString> UConventionKeeperConvention::GetAllTemplatedFoldersForCheck(const FString& DirectoryPath) const
// {
// 	// `/{ProjectName}/{CharacterName}/{SomethingName}`
// 	TArray<FString> TemplatedFolders = {};
// 	// UConventionKeeperBlueprintLibrary::GetDiskFoldersRelativeToRoot(DirectoryPath, TemplatedFolders);
// }

TSet<FString> UConventionKeeperConvention::ExtractTemplatesFromPath(
	const FString& Path,
	const TMap<FString, FString>& GlobalPlaceholders
)
{
	TSet<FString> OutFoundTemplates;
	// Split on forward‑slashes; cull empty to ignore leading/trailing “/”
	TArray<FString> Segments;
	Path.ParseIntoArray(Segments, TEXT("/"), /*InCullEmpty=*/ true);

	for (const FString& Segment : Segments)
	{
		// Look for a "{…}" folder segment
		if (Segment.Len() >= 3 &&
			Segment.StartsWith(TEXT("{")) &&
			Segment.EndsWith(TEXT("}")))
		{
			// strip braces
			FString Name = Segment.Mid(1, Segment.Len() - 2);

			// only add if it's not in the global ignore list
			if (!GlobalPlaceholders.Contains(Name))
			{
				OutFoundTemplates.Add(Name);
			}
		}
	}

	return OutFoundTemplates;
}

TArray<FString> UConventionKeeperConvention::ResolveTemplatePaths(
    const FString& FullPattern,
    const TMap<FString, FString>& GlobalPlaceholders
)
{
    TArray<FString> OutResults;

    // 1) Split the pattern into segments
    TArray<FString> Segments;
    FullPattern.ParseIntoArray(Segments, TEXT("/"), /*CullEmpty=*/ true);

    // 2) Find where the first placeholder appears
    int32 FirstTplIndex = 0;
    while (FirstTplIndex < Segments.Num())
    {
        const FString& Seg = Segments[FirstTplIndex];
        if (Seg.StartsWith(TEXT("{")) && Seg.EndsWith(TEXT("}")))
        {
            break;
        }
        ++FirstTplIndex;
    }

    // 3) Build the literal base path
    FString BasePath = TEXT("/");
    for (int32 i = 0; i < FirstTplIndex; ++i)
    {
        BasePath = FPaths::Combine(BasePath, Segments[i]);
    }

    IFileManager& FM = IFileManager::Get();
    if (!FM.DirectoryExists(*BasePath))
    {
        UE_LOG(LogTemp, Warning, TEXT("ResolveTemplatePaths: base path does not exist: %s"), *BasePath);
        return OutResults;
    }

    // 4) Start from the base path
    TArray<FString> CurrentPaths;
    CurrentPaths.Add(BasePath);

    // 5) For each segment after the base...
    for (int32 i = FirstTplIndex; i < Segments.Num(); ++i)
    {
        const FString& Seg = Segments[i];
        bool bIsTpl = Seg.StartsWith(TEXT("{")) && Seg.EndsWith(TEXT("}"));

        // If it's a literal segment, just descend into that folder
        if (!bIsTpl)
        {
            TArray<FString> NextPaths;
            for (const FString& P : CurrentPaths)
            {
                FString Candidate = FPaths::Combine(P, Seg);
                if (FM.DirectoryExists(*Candidate))
                {
                    NextPaths.Add(MoveTemp(Candidate));
                }
            }
            CurrentPaths = MoveTemp(NextPaths);
            continue;
        }

        // It's a placeholder
        FString TplName = Seg.Mid(1, Seg.Len() - 2);

        // If it's in global placeholders, treat it like a literal
        if (GlobalPlaceholders.Contains(TplName))
        {
            TArray<FString> NextPaths;
            for (const FString& P : CurrentPaths)
            {
                FString Candidate = FPaths::Combine(P, Seg);
                if (FM.DirectoryExists(*Candidate))
                {
                    NextPaths.Add(MoveTemp(Candidate));
                }
            }
            CurrentPaths = MoveTemp(NextPaths);
            continue;
        }

        // Otherwise, scan *all* subdirectories of each current path
        TArray<FString> NextPaths;
        for (const FString& P : CurrentPaths)
        {
            FM.IterateDirectory(*P,
                [&NextPaths](const TCHAR* ChildPath, bool bIsDir)
                {
                    if (!bIsDir) return true;
                    const FString ChildName = FPaths::GetCleanFilename(ChildPath);
                    if (ChildName == TEXT(".") || ChildName == TEXT(".."))
                        return true;
                    NextPaths.Add(FString(ChildPath));
                    return true;
                });
        }

        // Accumulate these matches at *this* template level
        OutResults.Append(NextPaths);
        CurrentPaths = MoveTemp(NextPaths);
    }

    return OutResults;
}
