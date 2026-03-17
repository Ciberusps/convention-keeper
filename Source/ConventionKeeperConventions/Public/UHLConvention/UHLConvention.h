// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ConventionKeeperConvention_Base.h"
#include "UHLConvention.generated.h"

UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew, AutoExpandCategories = ("Default"))
class CONVENTIONKEEPERCONVENTIONS_API UUHLConvention : public UConventionKeeperConvention_Base
{
	GENERATED_BODY()

public:
	UUHLConvention();

	virtual FText GetLocalizedRuleDescription(FName RuleId) const override;
};
