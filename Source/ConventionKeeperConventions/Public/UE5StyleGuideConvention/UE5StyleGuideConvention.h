// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ConventionKeeperConvention_Base.h"
#include "UE5StyleGuideConvention.generated.h"

/**
 * Convention based on Gamemakin UE5 Style Guide (v2).
 * Naming and structure rules are defined via Rules (e.g. naming-convention-pascalcase, asset-naming-*).
 */
UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew, AutoExpandCategories = ("Default"))
class CONVENTIONKEEPERCONVENTIONS_API UUE5StyleGuideConvention : public UConventionKeeperConvention_Base
{
	GENERATED_BODY()

public:
	UUE5StyleGuideConvention();
};
