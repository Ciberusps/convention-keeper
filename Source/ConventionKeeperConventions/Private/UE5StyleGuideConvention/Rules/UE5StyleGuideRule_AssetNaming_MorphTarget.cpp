// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MorphTarget.h"
#include "Animation/MorphTarget.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_MorphTarget)

UUE5StyleGuideRule_AssetNaming_MorphTarget::UUE5StyleGuideRule_AssetNaming_MorphTarget()
{
	RuleId = FName(TEXT("asset-naming-morph-target"));
	Description = FText::FromString(TEXT("Morph Target assets must use prefix MT_ (UE5 Style Guide 1.2.2)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-morph-target"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UMorphTarget::StaticClass() };
	Prefix = TEXT("MT_");
}
