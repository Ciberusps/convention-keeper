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
	/** Path pattern with placeholders (e.g. Content/{ProjectName}). All folder segments and assets under this path are checked. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (RelativePath))
	FDirectoryPath FolderPathPattern;

	virtual bool CanValidate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const override;
	virtual void Validate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) override;

	/** Return false if the folder segment name violates the convention. Default: pass. */
	UFUNCTION(BlueprintNativeEvent)
	bool IsNameValidForFolder(const FString& Name) const;
	virtual bool IsNameValidForFolder_Implementation(const FString& Name) const { return true; }

	/** Return false if the asset name violates the convention. Default: pass. */
	UFUNCTION(BlueprintNativeEvent)
	bool IsNameValidForAsset(const FString& Name) const;
	virtual bool IsNameValidForAsset_Implementation(const FString& Name) const { return true; }

	static bool IsRelevantPath(const FString& ResolvedPath, const TArray<FString>& SelectedPaths);
	static bool IsRelevantPath(const TArray<FString>& ResolvedPathsToCheck, const TArray<FString>& SelectedPaths);
	static bool IsPathUnderExcluded(const FString& ResolvedPath, const TArray<FString>& Exclusions, const TMap<FString, FString>& Placeholders);

private:
	static FString NormalizeRelativePath(const FString& InPath);
};
