// Pavel Penkov 2025 All Rights Reserved.

#include "EarendilConvention/Rules/EarendilConventionRule_AssetNaming_AnimSequence.h"
#include "Animation/AnimSequence.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(EarendilConventionRule_AssetNaming_AnimSequence)

UEarendilConventionRule_AssetNaming_AnimSequence::UEarendilConventionRule_AssetNaming_AnimSequence()
{
	RuleId = FName(TEXT("ec-asset-naming-anim-sequence"));
	Description = FText::FromString(TEXT("Animation Sequence assets must use prefix AS_ (EarendilConvention)."));
	DescriptionKey = FName(TEXT("RuleDesc_ec-asset-naming-anim-sequence"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UAnimSequence::StaticClass() };
	Prefix = TEXT("AS_");
}
