// Pavel Penkov 2025 All Rights Reserved.

#include "AssetTypeActions/ConventionAssetTypeActions.h"
#include "Convention.h"

#define LOCTEXT_NAMESPACE "ConventionAssetTypeActions"

FText FConventionTypeActions::GetName() const
{
	return LOCTEXT("ConventionTypeActionsName", "Convention");
}

FColor FConventionTypeActions::GetTypeColor() const
{
	return FColor(76, 175, 80);
}

UClass* FConventionTypeActions::GetSupportedClass() const
{
	return UConvention::StaticClass();
}

uint32 FConventionTypeActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

#undef LOCTEXT_NAMESPACE
