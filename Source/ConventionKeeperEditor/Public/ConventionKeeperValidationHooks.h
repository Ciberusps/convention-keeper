// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/Function.h"

class UConventionKeeperRule;

/**
 * Optional hooks for editor validation: slow-task progress and cancel between rules.
 * Used by UConventionKeeperCommandlet::ValidateData when running interactively (not commandlet).
 */
struct CONVENTIONKEEPEREDITOR_API FConventionKeeperValidationHooks
{
	TFunction<bool()> ShouldAbort;
	TFunction<void(int32 RuleIndex, int32 RuleCount, UConventionKeeperRule* Rule)> OnRuleProgress;
};
