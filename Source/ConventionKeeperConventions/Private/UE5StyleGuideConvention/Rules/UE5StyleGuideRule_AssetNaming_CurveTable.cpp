// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_CurveTable.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_CurveTable)

UUE5StyleGuideRule_AssetNaming_CurveTable::UUE5StyleGuideRule_AssetNaming_CurveTable()
{
	RuleId = FName(TEXT("asset-naming-curve-table"));
	Description = FText::FromString(TEXT("Curve Table assets must use prefix Curve_ and suffix _Table (UE5 Style Guide 1.2.7)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-curve-table"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.CurveTable"));
	Prefix = TEXT("Curve_");
	Suffix = TEXT("_Table");
}
