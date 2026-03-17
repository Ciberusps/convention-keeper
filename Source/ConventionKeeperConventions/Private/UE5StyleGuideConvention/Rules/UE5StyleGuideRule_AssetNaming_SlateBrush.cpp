// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SlateBrush.h"
#include "Slate/SlateBrushAsset.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_SlateBrush)

UUE5StyleGuideRule_AssetNaming_SlateBrush::UUE5StyleGuideRule_AssetNaming_SlateBrush()
{
	RuleId = FName(TEXT("asset-naming-slate-brush"));
	Description = FText::FromString(TEXT("Slate Brush assets must use prefix Brush_ (UE5 Style Guide 1.2.11)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-slate-brush"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { USlateBrushAsset::StaticClass() };
	Prefix = TEXT("Brush_");
}
