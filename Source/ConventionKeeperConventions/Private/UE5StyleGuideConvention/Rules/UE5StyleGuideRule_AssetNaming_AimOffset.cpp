// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AimOffset.h"
#include "Animation/AimOffsetBlendSpace.h"
#include "Animation/AimOffsetBlendSpace1D.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_AimOffset)

UUE5StyleGuideRule_AssetNaming_AimOffset::UUE5StyleGuideRule_AssetNaming_AimOffset()
{
	RuleId = FName(TEXT("asset-naming-aim-offset"));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-aim-offset"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UAimOffsetBlendSpace::StaticClass(), UAimOffsetBlendSpace1D::StaticClass() };
	Prefix = TEXT("AO_");
}
