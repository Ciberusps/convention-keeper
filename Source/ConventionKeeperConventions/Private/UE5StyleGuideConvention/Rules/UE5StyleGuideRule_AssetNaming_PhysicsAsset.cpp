// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_PhysicsAsset.h"
#include "PhysicsEngine/PhysicsAsset.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_PhysicsAsset)

UUE5StyleGuideRule_AssetNaming_PhysicsAsset::UUE5StyleGuideRule_AssetNaming_PhysicsAsset()
{
	RuleId = FName(TEXT("asset-naming-physics-asset"));
	Description = FText::FromString(TEXT("Physics Asset (skeletal collision) must use prefix PHYS_ (UE5 Style Guide 1.2.9)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-physics-asset"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UPhysicsAsset::StaticClass() };
	Prefix = TEXT("PHYS_");
}
