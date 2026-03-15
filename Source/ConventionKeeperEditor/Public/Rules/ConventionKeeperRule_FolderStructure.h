// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Rules/ConventionKeeperRule.h"
#include "ConventionKeeperRule_FolderStructure.generated.h"

class UConventionKeeperSettings;

UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew)
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

	virtual bool CanValidate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const override;
	virtual void Validate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) override;

	/** True if any of the rule paths is under one of the selected paths (so we only validate that folder). */
	static bool IsRelevantPath(const FString& ResolvedPath, const TArray<FString>& SelectedPaths);
	static bool IsRelevantPath(const TArray<FString>& ResolvedPathsToCheck, const TArray<FString>& SelectedPaths);

	/** True if path is under a folder exclusion or equals a file exclusion. Used by rules and tests. */
	static bool IsPathUnderExcluded(const FString& ResolvedPath, const TArray<FString>& Exclusions, const TMap<FString, FString>& Placeholders);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	void ConvertAllPathsToRelativePaths();
	static FString ResolvePlaceholdersForPath(const FString& DirectoryPath, const TMap<FString, FString>& Placeholders);
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
