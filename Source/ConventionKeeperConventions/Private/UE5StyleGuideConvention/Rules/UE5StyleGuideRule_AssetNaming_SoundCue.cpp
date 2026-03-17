// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SoundCue.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_SoundCue)

UUE5StyleGuideRule_AssetNaming_SoundCue::UUE5StyleGuideRule_AssetNaming_SoundCue()
{
	RuleId = FName(TEXT("asset-naming-sound-cue"));
	Description = FText::FromString(TEXT("Sound Cue assets must use prefix A_ and suffix _Cue (UE5 Style Guide 1.2.10)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-sound-cue"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.SoundCue"));
	Prefix = TEXT("A_");
	Suffix = TEXT("_Cue");
}
