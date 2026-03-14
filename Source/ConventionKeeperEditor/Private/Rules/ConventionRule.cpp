// Pavel Penkov 2025 All Rights Reserved.

#include "Rules/ConventionRule.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionRule)

bool UConventionRule::CanValidate_Implementation(const TArray<FString>& /*SelectedPaths*/, const TMap<FString, FString>& /*Placeholders*/) const
{
	return true;
}

void UConventionRule::Validate_Implementation(const TArray<FString>& /*SelectedPaths*/, const TMap<FString, FString>& /*Placeholders*/)
{
}
