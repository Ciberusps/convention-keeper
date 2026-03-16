// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BlendSpace.h"
#include "Animation/BlendSpace.h"
#include "Animation/BlendSpace1D.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_BlendSpace)

UUE5StyleGuideRule_AssetNaming_BlendSpace::UUE5StyleGuideRule_AssetNaming_BlendSpace()
{
	RuleId = FName(TEXT("asset-naming-blend-space"));
	Description = FText::FromString(TEXT("Blend Space (1D/2D) assets must use prefix BS_ (UE5 Style Guide 1.2.2)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-blend-space"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UBlendSpace::StaticClass(), UBlendSpace1D::StaticClass() };
	Prefix = TEXT("BS_");
}
