// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorValidatorBase.h"
#include "ConventionKeeperStateTreeDeprecatedNodesEditorValidator.generated.h"

class UStateTree;

UCLASS()
class CONVENTIONKEEPERVALIDATIONEDITOR_API UConventionKeeperStateTreeDeprecatedNodesEditorValidator : public UEditorValidatorBase
{
	GENERATED_BODY()

public:
	virtual bool CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InObject, FDataValidationContext& InContext) const override;
	virtual EDataValidationResult ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& Context) override;
};
