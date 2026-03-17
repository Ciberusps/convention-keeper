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
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_PhysicsAsset.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_DestructibleMesh.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Decal.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Texture.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Font.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SlateBrush.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SlateWidgetStyle.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_WidgetBlueprint.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_ParticleSystem.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SoundWave.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SoundCue.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SoundAttenuation.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SoundMix.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_ReverbEffect.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_DialogueVoice.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_DialogueWave.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MediaSoundWave.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SoundConcurrency.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetPlacement_SoundClass.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideConvention)

UUE5StyleGuideConvention::UUE5StyleGuideConvention()
{
	Name = TEXT("UE5 Style Guide");
	Description = FText::FromString(TEXT("Convention based on Gamemakin's UE5 Style Guide (v2): asset naming prefixes/suffixes, folder structure, PascalCase for names."));
	DocsLink = TEXT("https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file");
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
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_PhysicsAsset>(TEXT("Rule_AssetNaming_PhysicsAsset")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_DestructibleMesh>(TEXT("Rule_AssetNaming_DestructibleMesh")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_Decal>(TEXT("Rule_AssetNaming_Decal")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_Texture>(TEXT("Rule_AssetNaming_Texture")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_Font>(TEXT("Rule_AssetNaming_Font")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_SlateBrush>(TEXT("Rule_AssetNaming_SlateBrush")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_SlateWidgetStyle>(TEXT("Rule_AssetNaming_SlateWidgetStyle")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_WidgetBlueprint>(TEXT("Rule_AssetNaming_WidgetBlueprint")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_ParticleSystem>(TEXT("Rule_AssetNaming_ParticleSystem")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_SoundWave>(TEXT("Rule_AssetNaming_SoundWave")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_SoundCue>(TEXT("Rule_AssetNaming_SoundCue")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_SoundAttenuation>(TEXT("Rule_AssetNaming_SoundAttenuation")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_SoundMix>(TEXT("Rule_AssetNaming_SoundMix")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_ReverbEffect>(TEXT("Rule_AssetNaming_ReverbEffect")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_DialogueVoice>(TEXT("Rule_AssetNaming_DialogueVoice")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_DialogueWave>(TEXT("Rule_AssetNaming_DialogueWave")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_MediaSoundWave>(TEXT("Rule_AssetNaming_MediaSoundWave")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_SoundConcurrency>(TEXT("Rule_AssetNaming_SoundConcurrency")));
	Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetPlacement_SoundClass>(TEXT("Rule_AssetPlacement_SoundClass")));
}
