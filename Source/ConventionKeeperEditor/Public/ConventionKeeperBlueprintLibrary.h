// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ConventionKeeperBlueprintLibrary.generated.h"

/**
 * Shared path/template utilities for ConventionKeeper (conventions, rules, tests).
 */
UCLASS()
class CONVENTIONKEEPEREDITOR_API UConventionKeeperBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void MakePathRelativeToProjectDir(FString& InPath);
	static void GetDiskFoldersRelativeToRoot(const FString& DirectoryPath, TArray<FString>& FolderPaths);
	static void ConvertToFullPath(FString& InPath);

	/** Scans path for "{Name}" segments; ignores those in GlobalPlaceholders (keys with braces, e.g. "{ProjectName}"). Returns template names. */
	static TSet<FString> ExtractTemplatesFromPath(const FString& Path, const TMap<FString, FString>& GlobalPlaceholders);

    /**
     * Given a “templated” path (absolute or relative) with placeholders like
     * "{SomeTemplate}", this will:
     *  1) split off the leading literal segments (e.g. "/RootFolder"),
     *  2) for each placeholder segment, recurse into each matching subdirectory
     *     of the current set of paths,
     *  3) accumulate *all* matched folder‐paths at each placeholder level,
     *  4) return that list.
     *
     * Example:
     *   Pattern = "/RootFolder/{A}/{B}"
     *   Disk contains:
     *     /RootFolder/Foo
     *     /RootFolder/Bar
     *     /RootFolder/Foo/X
     *     /RootFolder/Foo/Y
     *
     *   ResolveTemplatePaths(Pattern) ->
     *     [ "/RootFolder/Foo",
     *       "/RootFolder/Bar",
     *       "/RootFolder/Foo/X",
     *       "/RootFolder/Foo/Y" ]
     */
	static TArray<FString> ResolveTemplatePaths(const FString& FullPattern, const TMap<FString, FString>& GlobalPlaceholders);

	/** Fills OutPathPlaceholders from resolved path using pattern. GlobalPlaceholders keys must include braces. Returns false if segment count or literal mismatch. */
	static bool ExtractPathPlaceholders(const FString& PatternPath, const FString& ResolvedPath, const TMap<FString, FString>& GlobalPlaceholders, TMap<FString, FString>& OutPathPlaceholders);
};
