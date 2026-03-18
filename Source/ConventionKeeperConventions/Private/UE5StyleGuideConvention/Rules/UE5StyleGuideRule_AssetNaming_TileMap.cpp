// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_TileMap.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_TileMap)

UUE5StyleGuideRule_AssetNaming_TileMap::UUE5StyleGuideRule_AssetNaming_TileMap()
{
	RuleId = FName(TEXT("asset-naming-tile-map"));
	Description = FText::FromString(TEXT("Tile Map (Paper 2D) assets must use prefix TM_ (UE5 Style Guide 1.2.8)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-tile-map"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Paper2D.PaperTileMap"));
	Prefix = TEXT("TM_");
}
