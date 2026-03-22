// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Rules/ConventionKeeperRule.h"
#include "ConventionKeeperRule_FolderStructure.generated.h"

class UConventionKeeperSettings;

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class CONVENTIONKEEPEREDITOR_API UConventionKeeperRule_FolderStructure : public UConventionKeeperRule
{
	GENERATED_BODY()

public:
	/**
	 * Base folder path (with placeholders, e.g. Content/{ProjectName}). This path must exist; under it RequiredFolders are checked and BannedFolders must not exist.
	 * If the path contains templates (e.g. {CharacterName}), validation runs for each resolved instance.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDirectoryPath FolderPath = {};

	/**
	 * Folders that must exist under FolderPath. Paths are relative to FolderPath and can use the same placeholders.
	 * Example: FolderPath = "Content/{ProjectName}", RequiredFolders = ["Characters", "Maps", "Core"] → Content/Game/Characters, Content/Game/Maps, Content/Game/Core must exist.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(RelativePath))
	TArray<FDirectoryPath> RequiredFolders = {};

	/**
	 * Folders that must not exist under FolderPath. If any of these paths exist, validation fails.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(RelativePath))
	TArray<FDirectoryPath> BannedFolders = {};

	/**
	 * When true, only the folders listed in RequiredFolders are allowed under FolderPath; any other subfolder causes an error.
	 * When false, RequiredFolders are only checked for existence; extra folders are allowed.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bOtherFoldersNotAllowed = false;

	/**
	 * Asset base names (without extension) that must exist directly under FolderPath. Non-recursive; .uasset and .umap.
	 * Placeholders like {CharacterName} are resolved the same way as in RequiredFolders.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> RequiredAssets = {};

	/**
	 * Asset base names that must not exist under FolderPath (same resolution rules as RequiredAssets).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> BannedAssets = {};

	/**
	 * When true, only assets whose resolved base names appear in RequiredAssets are allowed under FolderPath;
	 * any other .uasset / .umap in that directory (non-recursive) fails validation. Same folder match rules as RequiredAssets.
	 * When false, extra asset files are allowed if not listed in BannedAssets.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Other Assets Not Allowed"))
	bool bOtherAssetsNotAllowed = false;

	/**
	 * When true (default), this rule runs when validation is scoped to saved/selected asset package paths (e.g. on save).
	 * When false, the rule only runs for full scans or when a folder path is in the selected set — not for single-asset batches.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bValidateOnPerAssetSave = true;

	virtual bool CanValidate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const override;
	virtual void Validate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) override;

	/** True if any of the rule paths is under one of the selected paths (so we only validate that folder). */
	static bool IsRelevantPath(const FString& ResolvedPath, const TArray<FString>& SelectedPaths);
	static bool IsRelevantPath(const TArray<FString>& ResolvedPathsToCheck, const TArray<FString>& SelectedPaths);

	/** True if path is under a folder exclusion or equals a file exclusion. Used by rules and tests. */
	static bool IsPathUnderExcluded(const FString& ResolvedPath, const TArray<FString>& Exclusions, const TMap<FString, FString>& Placeholders);

	/** Replace {Key} substrings in a path or RequiredAssets/BannedAssets pattern (keys must include braces, e.g. {CharacterName}). */
	static FString ResolvePlaceholdersForPath(const FString& DirectoryPath, const TMap<FString, FString>& Placeholders);

	/** Non-recursive: base names of .uasset / .umap files directly in AbsoluteDir. */
	static void CollectAssetBaseNamesInDirectory(const FString& AbsoluteDir, TSet<FName>& OutNames);

	/**
	 * Scans AbsoluteBaseDir (non-recursive). Out paths are Content-relative, no extension (e.g. Content/Game/Gyms/Gym_Zombie),
	 * suitable for LogRuleMessage /FAssetNameToken. Patterns with empty or unresolved {…} are skipped.
	 */
	static void GatherRequiredBannedAssetViolations(
		const FString& AbsoluteBaseDir,
		const FString& ResolvedContentBasePath,
		const TArray<FString>& InRequiredAssets,
		const TArray<FString>& InBannedAssets,
		const TMap<FString, FString>& MergedPlaceholders,
		TArray<FString>& OutMissingRequiredContentPaths,
		TArray<FString>& OutPresentBannedContentPaths);

	/** Every .uasset/.umap base name on disk under AbsoluteBaseDir not in the resolved RequiredAssets set. */
	static void GatherDisallowedExtraAssets(
		const FString& AbsoluteBaseDir,
		const FString& ResolvedContentBasePath,
		const TArray<FString>& InRequiredAssets,
		const TMap<FString, FString>& MergedPlaceholders,
		TArray<FString>& OutDisallowedAssetContentPaths);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	void ConvertAllPathsToRelativePaths();
	static FString GetRequiredFolderProjectRelative(
		const FString& ResolvedBasePath,
		const FString& RequiredFolderPath,
		const TMap<FString, FString>& MergedPlaceholders);
	static FString GetAbsolutePathForRequiredSubfolder(
		const FString& ResolvedBasePath,
		const FString& RequiredFolderPath,
		const TMap<FString, FString>& MergedPlaceholders);
	static TArray<FString> GetConcreteBasePathsForFolderRule(const FString& FolderPathPath, const TMap<FString, FString>& Placeholders, const UConventionKeeperSettings* Settings, const TArray<FString>& SelectedPaths);
	static bool DoesDirectoryExist(const FString& DirectoryPath, const TMap<FString, FString>& Placeholders);
};
