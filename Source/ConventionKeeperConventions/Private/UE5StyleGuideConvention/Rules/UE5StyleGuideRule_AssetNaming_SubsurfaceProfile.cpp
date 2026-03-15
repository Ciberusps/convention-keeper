// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SubsurfaceProfile.h"
#include "Engine/SubsurfaceProfile.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_SubsurfaceProfile)

UUE5StyleGuideRule_AssetNaming_SubsurfaceProfile::UUE5StyleGuideRule_AssetNaming_SubsurfaceProfile()
{
	RuleId = FName(TEXT("asset-naming-subsurface-profile"));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-subsurface-profile"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { USubsurfaceProfile::StaticClass() };
	Prefix = TEXT("SP_");
}
