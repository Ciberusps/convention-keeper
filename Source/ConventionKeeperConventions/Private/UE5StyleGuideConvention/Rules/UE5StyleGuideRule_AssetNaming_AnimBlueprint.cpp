// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AnimBlueprint.h"
#include "Animation/AnimBlueprint.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_AnimBlueprint)

UUE5StyleGuideRule_AssetNaming_AnimBlueprint::UUE5StyleGuideRule_AssetNaming_AnimBlueprint()
{
	RuleId = FName(TEXT("asset-naming-anim-blueprint"));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-anim-blueprint"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UAnimBlueprint::StaticClass() };
	Prefix = TEXT("ABP_");
}
