// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SpriteAtlasGroup.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_SpriteAtlasGroup)

UUE5StyleGuideRule_AssetNaming_SpriteAtlasGroup::UUE5StyleGuideRule_AssetNaming_SpriteAtlasGroup()
{
	RuleId = FName(TEXT("asset-naming-sprite-atlas-group"));
	Description = FText::FromString(TEXT("Sprite Atlas Group (Paper 2D) assets must use prefix SPRG_ (UE5 Style Guide 1.2.8)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-sprite-atlas-group"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Paper2D.PaperSpriteAtlas"));
	Prefix = TEXT("SPRG_");
}
