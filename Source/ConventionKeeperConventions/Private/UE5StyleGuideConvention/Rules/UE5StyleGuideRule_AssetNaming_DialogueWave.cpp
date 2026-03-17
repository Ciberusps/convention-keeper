// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_DialogueWave.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_DialogueWave)

UUE5StyleGuideRule_AssetNaming_DialogueWave::UUE5StyleGuideRule_AssetNaming_DialogueWave()
{
	RuleId = FName(TEXT("asset-naming-dialogue-wave"));
	Description = FText::FromString(TEXT("Dialogue Wave assets must use prefix DW_ (UE5 Style Guide 1.2.10)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-dialogue-wave"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.DialogueWave"));
	Prefix = TEXT("DW_");
}
