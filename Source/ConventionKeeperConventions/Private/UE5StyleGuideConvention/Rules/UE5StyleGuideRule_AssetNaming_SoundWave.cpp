// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SoundWave.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_SoundWave)

UUE5StyleGuideRule_AssetNaming_SoundWave::UUE5StyleGuideRule_AssetNaming_SoundWave()
{
	RuleId = FName(TEXT("asset-naming-sound-wave"));
	Description = FText::FromString(TEXT("Sound Wave assets must use prefix A_ (UE5 Style Guide 1.2.10)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-sound-wave"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.SoundWave"));
	Prefix = TEXT("A_");
}
