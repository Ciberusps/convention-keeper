// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_CurveFloat.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_CurveFloat)

UUE5StyleGuideRule_AssetNaming_CurveFloat::UUE5StyleGuideRule_AssetNaming_CurveFloat()
{
	RuleId = FName(TEXT("asset-naming-curve-float"));
	Description = FText::FromString(TEXT("Float Curve assets must use prefix Curve_ and suffix _Float (UE5 Style Guide 1.2.7)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-curve-float"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.CurveFloat"));
	Prefix = TEXT("Curve_");
	Suffix = TEXT("_Float");
}
