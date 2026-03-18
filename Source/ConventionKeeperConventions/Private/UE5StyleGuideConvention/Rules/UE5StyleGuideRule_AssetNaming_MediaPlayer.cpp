// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MediaPlayer.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_MediaPlayer)

UUE5StyleGuideRule_AssetNaming_MediaPlayer::UUE5StyleGuideRule_AssetNaming_MediaPlayer()
{
	RuleId = FName(TEXT("asset-naming-media-player"));
	Description = FText::FromString(TEXT("Media Player assets must use prefix MP_ (UE5 Style Guide 1.2.7)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-media-player"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/MediaAssets.MediaPlayer"));
	Prefix = TEXT("MP_");
}
