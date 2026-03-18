// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_TileSet.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_TileSet)

UUE5StyleGuideRule_AssetNaming_TileSet::UUE5StyleGuideRule_AssetNaming_TileSet()
{
	RuleId = FName(TEXT("asset-naming-tile-set"));
	Description = FText::FromString(TEXT("Tile Set (Paper 2D) assets must use prefix TS_ (UE5 Style Guide 1.2.8)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-tile-set"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Paper2D.PaperTileSet"));
	Prefix = TEXT("TS_");
}
