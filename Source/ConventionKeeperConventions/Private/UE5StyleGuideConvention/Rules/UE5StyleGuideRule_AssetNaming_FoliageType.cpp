// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_FoliageType.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_FoliageType)

UUE5StyleGuideRule_AssetNaming_FoliageType::UUE5StyleGuideRule_AssetNaming_FoliageType()
{
	RuleId = FName(TEXT("asset-naming-foliage-type"));
	Description = FText::FromString(TEXT("Foliage Type assets must use prefix FT_ (UE5 Style Guide 1.2.7)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-foliage-type"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Foliage.FoliageType_InstancedStaticMesh"));
	AssetClassPaths.Add(TEXT("/Script/Foliage.FoliageType_Actor"));
	Prefix = TEXT("FT_");
}
