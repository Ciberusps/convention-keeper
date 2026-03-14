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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDirectoryPath FolderPath = {};

	// should be relative to FolderPath
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(RelativePath))
	TArray<FDirectoryPath> RequiredFolders = {};

	// should not exist
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(RelativePath))
	TArray<FDirectoryPath> BannedFolders = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bOtherFoldersNotAllowed = true;

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
	static FString NormalizeRelativePath(const FString& InPath);
	static TArray<FString> GetConcreteBasePathsForFolderRule(const FString& FolderPathPath, const TMap<FString, FString>& Placeholders, const UConventionKeeperSettings* Settings, const TArray<FString>& SelectedPaths);
	static bool DoesDirectoryExist(const FString& DirectoryPath, const TMap<FString, FString>& Placeholders);
};
