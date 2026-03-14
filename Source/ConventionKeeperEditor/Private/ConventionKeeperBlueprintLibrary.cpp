// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperBlueprintLibrary.h"
#include "HAL/FileManager.h"
#include "Misc/Paths.h"

static bool GetPlaceholderValue(const TMap<FString, FString>& GlobalPlaceholders, const FString& SegmentWithBraces, FString& OutValue)
{
	if (GlobalPlaceholders.Contains(SegmentWithBraces))
	{
		OutValue = GlobalPlaceholders[SegmentWithBraces];
		return true;
	}
	if (SegmentWithBraces.Len() > 2)
	{
		FString WithoutBraces = SegmentWithBraces.Mid(1, SegmentWithBraces.Len() - 2);
		if (GlobalPlaceholders.Contains(WithoutBraces))
		{
			OutValue = GlobalPlaceholders[WithoutBraces];
			return true;
		}
	}
	return false;
}

static void ResolveTemplatePathsRecurse(
	const FString& Prefix,
	const FString& PatternTail,
	const TMap<FString, FString>& GlobalPlaceholders,
	TArray<FString>& OutPaths)
{
	FString Normalized = PatternTail;
	Normalized.ReplaceInline(TEXT("\\"), TEXT("/"));
	Normalized.TrimStartAndEndInline();
	if (Normalized.IsEmpty())
	{
		OutPaths.Add(Prefix);
		return;
	}

	FString Segment;
	FString Rest;
	if (!Normalized.Split(TEXT("/"), &Segment, &Rest))
	{
		Segment = Normalized;
		Rest = FString();
	}

	if (Segment.StartsWith(TEXT("{")) && Segment.EndsWith(TEXT("}")))
	{
		FString Literal;
		if (GetPlaceholderValue(GlobalPlaceholders, Segment, Literal))
		{
			FString NewPrefix = Prefix.IsEmpty() ? Literal : (Prefix / Literal);
			ResolveTemplatePathsRecurse(NewPrefix, Rest, GlobalPlaceholders, OutPaths);
			return;
		}
		FString BasePath = FPaths::IsRelative(Prefix) ? (FPaths::ProjectDir() / Prefix) : Prefix;
		BasePath = FPaths::ConvertRelativePathToFull(BasePath);
		FPaths::NormalizeDirectoryName(BasePath);
		if (!BasePath.EndsWith(TEXT("/")) && !BasePath.EndsWith(TEXT("\\")))
		{
			BasePath += TEXT("/");
		}
		TArray<FString> SubDirs;
		IFileManager::Get().FindFiles(SubDirs, *(BasePath + TEXT("*")), false, true);
		for (const FString& Sub : SubDirs)
		{
			FString NewPrefix = Prefix.IsEmpty() ? Sub : (Prefix / Sub);
			ResolveTemplatePathsRecurse(NewPrefix, Rest, GlobalPlaceholders, OutPaths);
		}
		return;
	}

	FString NewPrefix = Prefix.IsEmpty() ? Segment : (Prefix / Segment);
	ResolveTemplatePathsRecurse(NewPrefix, Rest, GlobalPlaceholders, OutPaths);
}

TSet<FString> UConventionKeeperBlueprintLibrary::ExtractTemplatesFromPath(
	const FString& Path,
	const TMap<FString, FString>& GlobalPlaceholders)
{
	TSet<FString> Result;
	FString Remainder = Path;
	while (true)
	{
		const int32 Open = Remainder.Find(TEXT("{"), ESearchCase::CaseSensitive);
		if (Open == INDEX_NONE)
		{
			break;
		}
		const int32 Close = Remainder.Find(TEXT("}"), ESearchCase::CaseSensitive, ESearchDir::FromStart, Open);
		if (Close == INDEX_NONE)
		{
			break;
		}
		FString Segment = Remainder.Mid(Open + 1, Close - Open - 1).TrimStartAndEnd();
		Remainder = Remainder.Mid(Close + 1);
		if (Segment.Len() >= 1)
		{
			FString Key = FString::Printf(TEXT("{%s}"), *Segment);
			FString Dummy;
			if (!GetPlaceholderValue(GlobalPlaceholders, Key, Dummy))
			{
				Result.Add(Segment);
			}
		}
	}
	return Result;
}

TArray<FString> UConventionKeeperBlueprintLibrary::ResolveTemplatePaths(
	const FString& FullPattern,
	const TMap<FString, FString>& GlobalPlaceholders)
{
	TArray<FString> Out;
	FString Normalized = FullPattern;
	Normalized.ReplaceInline(TEXT("\\"), TEXT("/"));
	Normalized.TrimStartAndEndInline();
	while (Normalized.StartsWith(TEXT("/")))
	{
		Normalized.RemoveFromStart(TEXT("/"));
	}
	ResolveTemplatePathsRecurse(FString(), Normalized, GlobalPlaceholders, Out);
	for (FString& Path : Out)
	{
		Path.ReplaceInline(TEXT("\\"), TEXT("/"));
		if (FPaths::IsRelative(Path))
		{
			Path = FString(TEXT("/")) + Path;
		}
	}
	return Out;
}

bool UConventionKeeperBlueprintLibrary::ExtractPathPlaceholders(
	const FString& PatternPath,
	const FString& ResolvedPath,
	const TMap<FString, FString>& GlobalPlaceholders,
	TMap<FString, FString>& OutPathPlaceholders)
{
	OutPathPlaceholders.Empty();
	FString PatternNorm = PatternPath;
	PatternNorm.ReplaceInline(TEXT("\\"), TEXT("/"));
	PatternNorm.TrimStartAndEndInline();
	while (PatternNorm.StartsWith(TEXT("/")))
	{
		PatternNorm.RemoveFromStart(TEXT("/"));
	}
	FString ResolvedNorm = ResolvedPath;
	ResolvedNorm.ReplaceInline(TEXT("\\"), TEXT("/"));
	ResolvedNorm.TrimStartAndEndInline();
	while (ResolvedNorm.StartsWith(TEXT("/")))
	{
		ResolvedNorm.RemoveFromStart(TEXT("/"));
	}
	TArray<FString> PatternSegments;
	PatternNorm.ParseIntoArray(PatternSegments, TEXT("/"), true);
	TArray<FString> ResolvedSegments;
	ResolvedNorm.ParseIntoArray(ResolvedSegments, TEXT("/"), true);
	if (PatternSegments.Num() != ResolvedSegments.Num())
	{
		return false;
	}
	for (int32 i = 0; i < PatternSegments.Num(); ++i)
	{
		const FString& Seg = PatternSegments[i];
		if (Seg.StartsWith(TEXT("{")) && Seg.EndsWith(TEXT("}")))
		{
			FString ExpectedValue;
			if (GetPlaceholderValue(GlobalPlaceholders, Seg, ExpectedValue))
			{
				if (ExpectedValue != ResolvedSegments[i])
				{
					return false;
				}
				continue;
			}
			FString PlaceholderName = Seg.Mid(1, Seg.Len() - 2);
			OutPathPlaceholders.Add(PlaceholderName, ResolvedSegments[i]);
		}
		else if (Seg != ResolvedSegments[i])
		{
			return false;
		}
	}
	return true;
}

void UConventionKeeperBlueprintLibrary::MakePathRelativeToProjectDir(FString& InPath)
{
	const FString ProjectRoot = FPaths::ProjectDir();
	if (FPaths::MakePathRelativeTo(InPath, *ProjectRoot))
	{
		// Ensure we still have a trailing slash
		if (!InPath.EndsWith(TEXT("/")))
		{
			InPath += TEXT("/");
		}
	}
}

void UConventionKeeperBlueprintLibrary::GetDiskFoldersRelativeToRoot(
	const FString& DirectoryPath, TArray<FString>& FolderPaths)
{
	const FString ProjectRoot = FPaths::ProjectDir();
	
	// Ensure InPath ends with a slash
    FString Path = ProjectRoot / DirectoryPath;
    if (!Path.EndsWith(TEXT("/")) && !Path.EndsWith(TEXT("\\")))
    {
        Path += TEXT("/");
    }

    // FindFiles(Result, PathWithWildcard, Files, Directories): second arg is path+wildcard; use * to list all
    IFileManager::Get().FindFiles(FolderPaths, *(Path + TEXT("*")), /*Files=*/false, /*Directories=*/true);

    // Each entry in OutFolders is just the folder name (no path). If you want full paths:
    for (int32 i = 0; i < FolderPaths.Num(); ++i)
    {
    	FString PathRelativeToRoot = Path / FolderPaths[i]; 
        FPaths::MakePathRelativeTo(PathRelativeToRoot, *ProjectRoot);
        FolderPaths[i] = PathRelativeToRoot;
    }
}