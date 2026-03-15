// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MaterialInstance.h"
#include "Materials/MaterialInstanceConstant.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_MaterialInstance)

UUE5StyleGuideRule_AssetNaming_MaterialInstance::UUE5StyleGuideRule_AssetNaming_MaterialInstance()
{
	RuleId = FName(TEXT("asset-naming-material-instance"));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-material-instance"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UMaterialInstanceConstant::StaticClass() };
	Prefix = TEXT("MI_");
}
