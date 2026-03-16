// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_LevelSequence.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_LevelSequence)

UUE5StyleGuideRule_AssetNaming_LevelSequence::UUE5StyleGuideRule_AssetNaming_LevelSequence()
{
	RuleId = FName(TEXT("asset-naming-level-sequence"));
	Description = FText::FromString(TEXT("Level Sequence assets must use prefix LS_ (UE5 Style Guide 1.2.2)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-level-sequence"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths = { TEXT("/Script/LevelSequence.LevelSequence") };
	Prefix = TEXT("LS_");
}
