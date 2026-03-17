// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_ReverbEffect.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_ReverbEffect)

UUE5StyleGuideRule_AssetNaming_ReverbEffect::UUE5StyleGuideRule_AssetNaming_ReverbEffect()
{
	RuleId = FName(TEXT("asset-naming-reverb-effect"));
	Description = FText::FromString(TEXT("Reverb Effect assets must use prefix Reverb_ (UE5 Style Guide 1.2.10)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-reverb-effect"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.ReverbEffect"));
	Prefix = TEXT("Reverb_");
}
