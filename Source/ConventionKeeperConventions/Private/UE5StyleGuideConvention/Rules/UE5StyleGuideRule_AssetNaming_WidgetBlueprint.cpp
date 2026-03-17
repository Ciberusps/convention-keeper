// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_WidgetBlueprint.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_WidgetBlueprint)

UUE5StyleGuideRule_AssetNaming_WidgetBlueprint::UUE5StyleGuideRule_AssetNaming_WidgetBlueprint()
{
	RuleId = FName(TEXT("asset-naming-widget-blueprint"));
	Description = FText::FromString(TEXT("Widget Blueprint (UMG) assets must use prefix WBP_ (UE5 Style Guide 1.2.11)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-widget-blueprint"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/UMG.UserWidgetBlueprint"));
	AssetClassPaths.Add(TEXT("/Script/UMGEditor.WidgetBlueprint"));
	Prefix = TEXT("WBP_");
}
