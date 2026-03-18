// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_PaperFlipbook.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_PaperFlipbook)

UUE5StyleGuideRule_AssetNaming_PaperFlipbook::UUE5StyleGuideRule_AssetNaming_PaperFlipbook()
{
	RuleId = FName(TEXT("asset-naming-paper-flipbook"));
	Description = FText::FromString(TEXT("Paper Flipbook assets must use prefix PFB_ (UE5 Style Guide 1.2.8)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-paper-flipbook"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths = { TEXT("/Script/Paper2D.PaperFlipbook") };
	Prefix = TEXT("PFB_");
}
