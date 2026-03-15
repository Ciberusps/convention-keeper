// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Rules/ConventionKeeperRule.h"
#include "ConventionKeeperRule_NamingConvention.generated.h"

/**
 * Base rule for naming conventions: validates folder and asset names in a path scope.
 * Subclasses override IsNameValidForFolder / IsNameValidForAsset to implement the actual convention (e.g. PascalCase).
 */
UCLASS(Abstract, BlueprintType, DefaultToInstanced, EditInlineNew)
class CONVENTIONKEEPEREDITOR_API UConventionKeeperRule_NamingConvention : public UConventionKeeperRule
{
	GENERATED_BODY()

public:
	/**
	 * Root path (with placeholders) inside which folder and asset names are validated. Example: "Content/{ProjectName}".
	 * All folder segments and assets under the resolved path are checked by IsNameValidForFolder / IsNameValidForAsset.
	 * Paths under Settings Exclusions are skipped. When the user selects a single asset, only that asset and its parent folder are checked.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (RelativePath))
	FDirectoryPath FolderPathPattern;

	virtual bool CanValidate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const override;
	virtual void Validate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) override;

	/** Override: return false if the folder segment name (one path segment) violates the convention. Default: always true. */
	UFUNCTION(BlueprintNativeEvent)
	bool IsNameValidForFolder(const FString& Name) const;
	virtual bool IsNameValidForFolder_Implementation(const FString& Name) const { return true; }

	/** Override: return false if the asset name (no path, just the asset name) violates the convention. Default: always true. */
	UFUNCTION(BlueprintNativeEvent)
	bool IsNameValidForAsset(const FString& Name) const;
	virtual bool IsNameValidForAsset_Implementation(const FString& Name) const { return true; }

	/** Override: return a short hint for the user when name is invalid (e.g. "Use PascalCase. Segment 'ab' must start with uppercase."). Appended after the generic message in the log. */
	virtual FText GetValidationErrorHint(const FString& Name, bool bIsFolder) const { return FText(); }

	static bool IsRelevantPath(const FString& ResolvedPath, const TArray<FString>& SelectedPaths);
	static bool IsRelevantPath(const TArray<FString>& ResolvedPathsToCheck, const TArray<FString>& SelectedPaths);
	static bool IsPathUnderExcluded(const FString& ResolvedPath, const TArray<FString>& Exclusions, const TMap<FString, FString>& Placeholders);

private:
	static FString NormalizeRelativePath(const FString& InPath);
};
