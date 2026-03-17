// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SoundAttenuation.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_SoundAttenuation)

UUE5StyleGuideRule_AssetNaming_SoundAttenuation::UUE5StyleGuideRule_AssetNaming_SoundAttenuation()
{
	RuleId = FName(TEXT("asset-naming-sound-attenuation"));
	Description = FText::FromString(TEXT("Sound Attenuation assets must use prefix ATT_ (UE5 Style Guide 1.2.10)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-sound-attenuation"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.SoundAttenuation"));
	Prefix = TEXT("ATT_");
}
