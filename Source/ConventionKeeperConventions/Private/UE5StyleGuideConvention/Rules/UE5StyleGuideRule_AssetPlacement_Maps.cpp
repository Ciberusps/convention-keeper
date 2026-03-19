// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetPlacement_Maps.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetPlacement_Maps)

UUE5StyleGuideRule_AssetPlacement_Maps::UUE5StyleGuideRule_AssetPlacement_Maps()
{
	RuleId = FName(TEXT("asset-placement-maps"));
	Description = FText::FromString(TEXT("Level/Map (World) assets must be in a folder named Maps (UE5 Style Guide 2.4)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-placement-maps"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.World"));
	RequiredPathSegment = TEXT("Maps");
}
