// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_ForceFeedbackEffect.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_ForceFeedbackEffect)

UUE5StyleGuideRule_AssetNaming_ForceFeedbackEffect::UUE5StyleGuideRule_AssetNaming_ForceFeedbackEffect()
{
	RuleId = FName(TEXT("asset-naming-force-feedback-effect"));
	Description = FText::FromString(TEXT("Force Feedback Effect assets must use prefix FFE_ (UE5 Style Guide 1.2.7)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-force-feedback-effect"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.ForceFeedbackEffect"));
	Prefix = TEXT("FFE_");
}
