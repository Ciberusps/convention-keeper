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
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AIController.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BehaviorTree.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Blackboard.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BTDecorator.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BTService.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BTTask.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_EnvQuery.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_EnvQueryContext.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Material.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MaterialFunction.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MaterialInstance.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MaterialParameterCollection.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SubsurfaceProfile.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_PhysicalMaterial.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Decal.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Texture.h"

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
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_AIController>(TEXT("Rule_AssetNaming_AIController")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_BehaviorTree>(TEXT("Rule_AssetNaming_BehaviorTree")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_Blackboard>(TEXT("Rule_AssetNaming_Blackboard")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_BTDecorator>(TEXT("Rule_AssetNaming_BTDecorator")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_BTService>(TEXT("Rule_AssetNaming_BTService")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_BTTask>(TEXT("Rule_AssetNaming_BTTask")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_EnvQuery>(TEXT("Rule_AssetNaming_EnvQuery")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_EnvQueryContext>(TEXT("Rule_AssetNaming_EnvQueryContext")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_Material>(TEXT("Rule_AssetNaming_Material")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_MaterialFunction>(TEXT("Rule_AssetNaming_MaterialFunction")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_MaterialInstance>(TEXT("Rule_AssetNaming_MaterialInstance")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_MaterialParameterCollection>(TEXT("Rule_AssetNaming_MaterialParameterCollection")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_SubsurfaceProfile>(TEXT("Rule_AssetNaming_SubsurfaceProfile")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_PhysicalMaterial>(TEXT("Rule_AssetNaming_PhysicalMaterial")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_Decal>(TEXT("Rule_AssetNaming_Decal")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_Texture>(TEXT("Rule_AssetNaming_Texture")));
}
