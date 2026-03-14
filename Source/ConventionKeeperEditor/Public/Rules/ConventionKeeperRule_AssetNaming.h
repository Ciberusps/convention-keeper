// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Rules/ConventionKeeperRule.h"
#include "ConventionKeeperRule_AssetNaming.generated.h"

/**
 * Rule: assets in a templated folder path must follow a naming pattern.
 * - Folder path can contain placeholders (e.g. Content/{ProjectName}/Characters/{CharacterName}/Animations).
 * - AssetClasses: only these classes are checked.
 * - NamingTemplate: e.g. "AS_{CharacterName}_" — placeholders are filled from the folder path; the rest of the name is free,
 *   but if it ends with _<number>, that number must be zero-padded to NumberPaddingDigits (e.g. AS_Zombie_Jump_01 not _1).
 * - Optional Prefix/Suffix for simpler fixed prefix/suffix checks.
 */
UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew)
class CONVENTIONKEEPEREDITOR_API UConventionKeeperRule_AssetNaming : public UConventionKeeperRule
{
	GENERATED_BODY()

public:
	/** Folder path pattern with placeholders (e.g. Content/{ProjectName}/Characters/{CharacterName}/Animations). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (RelativePath))
	FDirectoryPath FolderPathPattern;

	/** Asset classes to validate (e.g. AnimSequence, AnimMontage). Only these classes in the folder are checked. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses = "/Script/CoreUObject.Object"))
	TArray<TSubclassOf<UObject>> AssetClasses;

	/**
	 * Naming template. Placeholders like {CharacterName} are replaced from the folder path.
	 * Example: "AS_{CharacterName}_" → in folder .../Zombie/Animations required prefix is "AS_Zombie_".
	 * If the asset name ends with _<digits>, that suffix must be zero-padded to NumberPaddingDigits (e.g. _01 not _1).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NamingTemplate;

	/** When the name has a trailing numeric suffix, it must be zero-padded to this many digits (e.g. 2 → 01, 02). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberPaddingDigits = 2;

	/** Optional fixed prefix (applied if non-empty; can be used instead of or with NamingTemplate). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Prefix;

	/** Optional fixed suffix (applied if non-empty). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Suffix;

	virtual bool CanValidate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const override;
	virtual void Validate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) override;

	/** Returns the required prefix for an asset name given path placeholder values (e.g. CharacterName=Zombie). */
	static FString ResolveNamingTemplate(const FString& Template, const TMap<FString, FString>& PathPlaceholders);
	/** If Name ends with _<digits>, returns true when that part is zero-padded to PaddingDigits (e.g. _01). */
	static bool IsNumberSuffixValid(const FString& AssetName, int32 PaddingDigits);
	/** Suggested corrected name when only the number suffix is wrong (e.g. AS_Zombie_Jump_1 → AS_Zombie_Jump_01). */
	static FString SuggestZeroPaddedName(const FString& AssetName, int32 PaddingDigits);

	/** Fills OutPathPlaceholders from resolved path using pattern with {Placeholder} segments. GlobalPlaceholders keys must include braces (e.g. "{ProjectName}"). */
	static bool ExtractPathPlaceholders(const FString& PatternPath, const FString& ResolvedPath, const TMap<FString, FString>& GlobalPlaceholders, TMap<FString, FString>& OutPathPlaceholders);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	static FString NormalizeRelativePath(const FString& InPath);
	static bool IsRelevantPath(const FString& ResolvedPath, const TArray<FString>& SelectedPaths);
	static bool IsPathUnderExcluded(const FString& ResolvedPath, const TArray<FString>& ExcludeFolders, const TMap<FString, FString>& Placeholders);
};
