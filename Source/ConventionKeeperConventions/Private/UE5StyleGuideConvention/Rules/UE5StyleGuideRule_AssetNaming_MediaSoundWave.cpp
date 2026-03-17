// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MediaSoundWave.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_MediaSoundWave)

UUE5StyleGuideRule_AssetNaming_MediaSoundWave::UUE5StyleGuideRule_AssetNaming_MediaSoundWave()
{
	RuleId = FName(TEXT("asset-naming-media-sound-wave"));
	Description = FText::FromString(TEXT("Media Sound Wave assets must use prefix MSW_ (UE5 Style Guide 1.2.10)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-media-sound-wave"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/MediaAssets.MediaSoundWave"));
	Prefix = TEXT("MSW_");
}
