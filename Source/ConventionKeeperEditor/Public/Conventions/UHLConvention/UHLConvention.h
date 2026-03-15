// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ConventionKeeperConvention.h"
#include "UHLConvention.generated.h"


UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew, AutoExpandCategories = ("Default"))
class CONVENTIONKEEPEREDITOR_API UUHLConvention : public UConventionKeeperConvention
{
	GENERATED_BODY()

public:
	UUHLConvention();

	virtual FText GetLocalizedRuleDescription(FName RuleId) const override;
};
