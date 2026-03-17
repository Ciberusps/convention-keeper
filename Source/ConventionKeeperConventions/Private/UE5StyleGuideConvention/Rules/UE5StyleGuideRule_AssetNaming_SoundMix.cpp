// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SoundMix.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_SoundMix)

UUE5StyleGuideRule_AssetNaming_SoundMix::UUE5StyleGuideRule_AssetNaming_SoundMix()
{
	RuleId = FName(TEXT("asset-naming-sound-mix"));
	Description = FText::FromString(TEXT("Sound Mix assets must use prefix Mix_ (UE5 Style Guide 1.2.10)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-sound-mix"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.SoundMix"));
	Prefix = TEXT("Mix_");
}
