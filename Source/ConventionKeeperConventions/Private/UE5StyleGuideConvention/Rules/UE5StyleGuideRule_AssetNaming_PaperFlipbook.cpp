// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_PaperFlipbook.h"
#include "PaperFlipbook.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_PaperFlipbook)

UUE5StyleGuideRule_AssetNaming_PaperFlipbook::UUE5StyleGuideRule_AssetNaming_PaperFlipbook()
{
	RuleId = FName(TEXT("asset-naming-paper-flipbook"));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-paper-flipbook"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UPaperFlipbook::StaticClass() };
	Prefix = TEXT("PFB_");
}
