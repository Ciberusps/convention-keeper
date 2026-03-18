// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_LandscapeGrassType.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_LandscapeGrassType)

UUE5StyleGuideRule_AssetNaming_LandscapeGrassType::UUE5StyleGuideRule_AssetNaming_LandscapeGrassType()
{
	RuleId = FName(TEXT("asset-naming-landscape-grass-type"));
	Description = FText::FromString(TEXT("Landscape Grass Type assets must use prefix LG_ (UE5 Style Guide 1.2.7)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-landscape-grass-type"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Landscape.LandscapeGrassType"));
	Prefix = TEXT("LG_");
}
