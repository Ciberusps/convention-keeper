// Pavel Penkov 2025 All Rights Reserved.

#include "Rules/ConventionKeeperRule.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperRule)

bool UConventionKeeperRule::CanValidate_Implementation(const TArray<FString>& /*SelectedPaths*/, const TMap<FString, FString>& /*Placeholders*/) const
{
	return true;
}

void UConventionKeeperRule::Validate_Implementation(const TArray<FString>& /*SelectedPaths*/, const TMap<FString, FString>& /*Placeholders*/)
{
}
