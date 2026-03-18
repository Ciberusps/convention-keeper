// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Sprite.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_Sprite)

UUE5StyleGuideRule_AssetNaming_Sprite::UUE5StyleGuideRule_AssetNaming_Sprite()
{
	RuleId = FName(TEXT("asset-naming-sprite"));
	Description = FText::FromString(TEXT("Sprite (Paper 2D) assets must use prefix SPR_ (UE5 Style Guide 1.2.8)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-sprite"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Paper2D.PaperSprite"));
	Prefix = TEXT("SPR_");
}
