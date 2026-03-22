// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ConventionKeeperConvention_Base.h"
#include "EarendilConvention.generated.h"

/**
 * EarendilConvention: default convention for the Convention Keeper plugin. Extends UE5 Style Guide via ExtendsConvention,
 * overrides asset-naming-anim-sequence to use prefix AS_ (not A_), and adds folder-structure and character animation rules.
 */
UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew, DisplayName="Earendil Convention (recommended)", AutoExpandCategories = ("Default"))
class CONVENTIONKEEPERCONVENTIONS_API UEarendilConvention : public UConventionKeeperConvention_Base
{
	GENERATED_BODY()

public:
	UEarendilConvention();

	virtual FText GetLocalizedRuleDescription(FName RuleId) const override;
};
