// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_CurveVector.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_CurveVector)

UUE5StyleGuideRule_AssetNaming_CurveVector::UUE5StyleGuideRule_AssetNaming_CurveVector()
{
	RuleId = FName(TEXT("asset-naming-curve-vector"));
	Description = FText::FromString(TEXT("Vector Curve assets must use prefix Curve_ and suffix _Vector (UE5 Style Guide 1.2.7)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-curve-vector"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.CurveVector"));
	Prefix = TEXT("Curve_");
	Suffix = TEXT("_Vector");
}
