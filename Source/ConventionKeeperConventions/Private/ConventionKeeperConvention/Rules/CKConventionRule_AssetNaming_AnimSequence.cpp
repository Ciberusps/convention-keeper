// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperConvention/Rules/CKConventionRule_AssetNaming_AnimSequence.h"
#include "Animation/AnimSequence.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CKConventionRule_AssetNaming_AnimSequence)

UCKConventionRule_AssetNaming_AnimSequence::UCKConventionRule_AssetNaming_AnimSequence()
{
	RuleId = FName(TEXT("ck-asset-naming-anim-sequence"));
	Description = FText::FromString(TEXT("Animation Sequence assets must use prefix AS_ (CKConvention)."));
	DescriptionKey = FName(TEXT("RuleDesc_ck-asset-naming-anim-sequence"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UAnimSequence::StaticClass() };
	Prefix = TEXT("AS_");
}
