// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_LandscapeLayer.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_LandscapeLayer)

UUE5StyleGuideRule_AssetNaming_LandscapeLayer::UUE5StyleGuideRule_AssetNaming_LandscapeLayer()
{
	RuleId = FName(TEXT("asset-naming-landscape-layer"));
	Description = FText::FromString(TEXT("Landscape Layer (Layer Info) assets must use prefix LL_ (UE5 Style Guide 1.2.7)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-landscape-layer"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Landscape.LandscapeLayerInfoObject"));
	Prefix = TEXT("LL_");
}
