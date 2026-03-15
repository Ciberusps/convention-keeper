// Pavel Penkov 2025 All Rights Reserved.

#include "Rules/ConventionKeeperRule.h"

#include "Localization/ConventionKeeperLocalization.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperRule)

FText UConventionKeeperRule::GetDisplayDescription() const
{
	if (!DescriptionKey.IsNone())
	{
		return ConventionKeeperLoc::GetText(DescriptionKey);
	}
	return Description;
}

bool UConventionKeeperRule::CanValidate_Implementation(const TArray<FString>& /*SelectedPaths*/, const TMap<FString, FString>& /*Placeholders*/) const
{
	return true;
}

void UConventionKeeperRule::Validate_Implementation(const TArray<FString>& /*SelectedPaths*/, const TMap<FString, FString>& /*Placeholders*/)
{
}

FString UConventionKeeperRule::NormalizeRelativePath(const FString& InPath)
{
	FString Result = InPath;
	Result.ReplaceInline(TEXT("\\"), TEXT("/"));
	if (!Result.EndsWith(TEXT("/")))
	{
		Result += TEXT("/");
	}
	return Result;
}
