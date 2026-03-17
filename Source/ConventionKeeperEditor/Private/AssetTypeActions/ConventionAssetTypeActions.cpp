// Pavel Penkov 2025 All Rights Reserved.

#include "AssetTypeActions/ConventionAssetTypeActions.h"
#include "ConventionKeeperConvention_Base.h"
#include "ConventionKeeperEditorStyle.h"

#define LOCTEXT_NAMESPACE "ConventionAssetTypeActions"

static const FName ConventionAssetIconName("ConventionKeeperEditor.ConventionAssetIcon");

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
	return UConventionKeeperConvention_Base::StaticClass();
}

uint32 FConventionTypeActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

const FSlateBrush* FConventionTypeActions::GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const
{
	return FConventionKeeperEditorStyle::Get().GetBrush(ConventionAssetIconName);
}

const FSlateBrush* FConventionTypeActions::GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const
{
	return FConventionKeeperEditorStyle::Get().GetBrush(ConventionAssetIconName);
}

#undef LOCTEXT_NAMESPACE
