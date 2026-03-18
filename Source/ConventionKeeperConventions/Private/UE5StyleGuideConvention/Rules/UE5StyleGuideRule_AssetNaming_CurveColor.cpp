// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_CurveColor.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_CurveColor)

UUE5StyleGuideRule_AssetNaming_CurveColor::UUE5StyleGuideRule_AssetNaming_CurveColor()
{
	RuleId = FName(TEXT("asset-naming-curve-color"));
	Description = FText::FromString(TEXT("Color Curve assets must use prefix Curve_ and suffix _Color (UE5 Style Guide 1.2.7)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-curve-color"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.CurveLinearColor"));
	Prefix = TEXT("Curve_");
	Suffix = TEXT("_Color");
}
