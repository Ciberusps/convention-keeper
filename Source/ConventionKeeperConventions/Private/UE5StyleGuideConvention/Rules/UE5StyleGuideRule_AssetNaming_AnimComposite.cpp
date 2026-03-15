// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AnimComposite.h"
#include "Animation/AnimComposite.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_AnimComposite)

UUE5StyleGuideRule_AssetNaming_AnimComposite::UUE5StyleGuideRule_AssetNaming_AnimComposite()
{
	RuleId = FName(TEXT("asset-naming-anim-composite"));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-anim-composite"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UAnimComposite::StaticClass() };
	Prefix = TEXT("AC_");
}
