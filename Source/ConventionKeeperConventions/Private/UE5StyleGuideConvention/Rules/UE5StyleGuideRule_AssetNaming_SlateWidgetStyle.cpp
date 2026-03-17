// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SlateWidgetStyle.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_SlateWidgetStyle)

UUE5StyleGuideRule_AssetNaming_SlateWidgetStyle::UUE5StyleGuideRule_AssetNaming_SlateWidgetStyle()
{
	RuleId = FName(TEXT("asset-naming-slate-widget-style"));
	Description = FText::FromString(TEXT("Slate Widget Style assets must use prefix Style_ (UE5 Style Guide 1.2.11)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-slate-widget-style"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/SlateCore.SlateWidgetStyleAsset"));
	Prefix = TEXT("Style_");
}
