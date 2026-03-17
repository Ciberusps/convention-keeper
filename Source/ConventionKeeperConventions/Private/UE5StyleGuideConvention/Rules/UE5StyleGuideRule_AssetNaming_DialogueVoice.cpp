// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_DialogueVoice.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_DialogueVoice)

UUE5StyleGuideRule_AssetNaming_DialogueVoice::UUE5StyleGuideRule_AssetNaming_DialogueVoice()
{
	RuleId = FName(TEXT("asset-naming-dialogue-voice"));
	Description = FText::FromString(TEXT("Dialogue Voice assets must use prefix DV_ (UE5 Style Guide 1.2.10)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-dialogue-voice"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.DialogueVoice"));
	Prefix = TEXT("DV_");
}
