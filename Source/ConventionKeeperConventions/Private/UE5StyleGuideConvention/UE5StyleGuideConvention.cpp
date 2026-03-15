// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/UE5StyleGuideConvention.h"
#include "Rules/ConventionKeeperRule_NamingConvention_PascalCase.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AnimSequence.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AnimMontage.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AnimBlueprint.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BlendSpace.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AimOffset.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AnimComposite.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_LevelSequence.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MorphTarget.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_PaperFlipbook.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_ControlRig.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SkeletalMesh.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Skeleton.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideConvention)

UUE5StyleGuideConvention::UUE5StyleGuideConvention()
{
	Name = TEXT("UE5 Style Guide");
	Rules.Add(CreateDefaultSubobject<UConventionKeeperRule_NamingConvention_PascalCase>(TEXT("Rule_NamingConvention_PascalCase")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_AnimSequence>(TEXT("Rule_AssetNaming_AnimSequence")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_AnimMontage>(TEXT("Rule_AssetNaming_AnimMontage")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_AnimBlueprint>(TEXT("Rule_AssetNaming_AnimBlueprint")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_BlendSpace>(TEXT("Rule_AssetNaming_BlendSpace")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_AimOffset>(TEXT("Rule_AssetNaming_AimOffset")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_AnimComposite>(TEXT("Rule_AssetNaming_AnimComposite")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_LevelSequence>(TEXT("Rule_AssetNaming_LevelSequence")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_MorphTarget>(TEXT("Rule_AssetNaming_MorphTarget")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_PaperFlipbook>(TEXT("Rule_AssetNaming_PaperFlipbook")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_ControlRig>(TEXT("Rule_AssetNaming_ControlRig")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_SkeletalMesh>(TEXT("Rule_AssetNaming_SkeletalMesh")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_Skeleton>(TEXT("Rule_AssetNaming_Skeleton")));
}
