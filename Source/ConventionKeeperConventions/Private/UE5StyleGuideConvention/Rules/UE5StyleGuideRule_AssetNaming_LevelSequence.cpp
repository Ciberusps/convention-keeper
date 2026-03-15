// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_LevelSequence.h"
#include "LevelSequence.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_LevelSequence)

UUE5StyleGuideRule_AssetNaming_LevelSequence::UUE5StyleGuideRule_AssetNaming_LevelSequence()
{
	RuleId = FName(TEXT("asset-naming-level-sequence"));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-level-sequence"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { ULevelSequence::StaticClass() };
	Prefix = TEXT("LS_");
}
