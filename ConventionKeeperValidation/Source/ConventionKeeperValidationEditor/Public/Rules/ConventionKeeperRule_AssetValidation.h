// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Rules/ConventionKeeperRule.h"
#include "EditorValidatorBase.h"
#include "ConventionKeeperRule_AssetValidation.generated.h"

class UConventionKeeperSettings;

/**
 * Runs a single UEditorValidatorBase (Data Validation plugin) over assets under ValidationRoot,
 * and reports results into the Convention Keeper Message Log.
 *
 * Provided by the optional ConventionKeeperValidation plugin (no engine plugin deps on core ConventionKeeper).
 */
UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class CONVENTIONKEEPERVALIDATIONEDITOR_API UConventionKeeperRule_AssetValidation : public UConventionKeeperRule
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asset Validation")
	FDirectoryPath ValidationRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asset Validation")
	bool bRecursive = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asset Validation")
	TSubclassOf<UEditorValidatorBase> EditorValidatorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asset Validation")
	TArray<TSubclassOf<UObject>> LimitToAssetTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asset Validation")
	bool bRunClassIsDataValid = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asset Validation")
	bool bValidateOnPerAssetSave = true;

	virtual bool CanValidate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const override;
	virtual void Validate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) override;
};
