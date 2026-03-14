// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ConventionKeeperNamingConvention.h"
#include "Rules/ConventionRule.h"
#include "ConventionKeeperConvention.generated.h"

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class CONVENTIONKEEPEREDITOR_API UConventionKeeperConvention : public UObject
{
	GENERATED_BODY()

public:
	// should introspect all templates recursively
	// e.g. we can have `/{ProjectName}/{CharacterName}/{SomethingName}`
	// {ProjectName} - placeholder, {CharacterName} and {SomethingName} are templates
	/**
	 * Scans a single path string for segments of the form "{Name}",
	 * ignores any in GlobalPlaceholders, and returns the rest.
	 */
	UFUNCTION()
	static TSet<FString> ExtractTemplatesFromPath(
		const FString& Path,
		const TMap<FString, FString>& GlobalPlaceholders
	);

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
	UFUNCTION()
	static TArray<FString> ResolveTemplatePaths(
		const FString& FullPattern,
		const TMap<FString, FString>& GlobalPlaceholders
	);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UConventionRule>> Rules = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UConventionKeeperNamingConvention> NamingConvention;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ValidateFolderStructures();
	void ValidateFolderStructures_Implementation();

	UFUNCTION(BlueprintCallable)
	void ValidateFolderStructuresForPaths(const TArray<FString>& SelectedPaths);

	bool DoesDirectoryExist(const FString& DirectoryPath, const TMap<FString, FString>& Placeholders);

};
