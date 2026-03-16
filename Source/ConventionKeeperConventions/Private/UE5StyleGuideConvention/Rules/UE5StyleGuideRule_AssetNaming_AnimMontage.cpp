// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AnimMontage.h"
#include "Animation/AnimMontage.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_AnimMontage)

UUE5StyleGuideRule_AssetNaming_AnimMontage::UUE5StyleGuideRule_AssetNaming_AnimMontage()
{
	RuleId = FName(TEXT("asset-naming-anim-montage"));
	Description = FText::FromString(TEXT("Animation Montage assets must use prefix AM_ (UE5 Style Guide 1.2.2)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-anim-montage"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UAnimMontage::StaticClass() };
	Prefix = TEXT("AM_");
}
