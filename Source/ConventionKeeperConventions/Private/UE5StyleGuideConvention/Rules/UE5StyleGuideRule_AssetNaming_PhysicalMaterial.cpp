// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_PhysicalMaterial.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_PhysicalMaterial)

UUE5StyleGuideRule_AssetNaming_PhysicalMaterial::UUE5StyleGuideRule_AssetNaming_PhysicalMaterial()
{
	RuleId = FName(TEXT("asset-naming-physical-material"));
	Description = FText::FromString(TEXT("Physical Material assets must use prefix PM_ (UE5 Style Guide 1.2.9)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-physical-material"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UPhysicalMaterial::StaticClass() };
	Prefix = TEXT("PM_");
}
