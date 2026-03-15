// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AnimSequence.h"
#include "Animation/AnimSequence.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_AnimSequence)

UUE5StyleGuideRule_AssetNaming_AnimSequence::UUE5StyleGuideRule_AssetNaming_AnimSequence()
{
	RuleId = FName(TEXT("asset-naming-anim-sequence"));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-anim-sequence"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UAnimSequence::StaticClass() };
	Prefix = TEXT("A_");
}
