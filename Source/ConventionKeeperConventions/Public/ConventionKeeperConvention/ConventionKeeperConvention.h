// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UE5StyleGuideConvention/UE5StyleGuideConvention.h"
#include "ConventionKeeperConvention.generated.h"

/**
 * Default convention for the Convention Keeper plugin. Extends UE5 Style Guide (no extra rules).
 * Use this as the default in project settings or as a base to extend.
 */
UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew, AutoExpandCategories = ("Default"))
class CONVENTIONKEEPERCONVENTIONS_API UConventionKeeperConvention : public UUE5StyleGuideConvention
{
	GENERATED_BODY()

public:
	UConventionKeeperConvention();
};
