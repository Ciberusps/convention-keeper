// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Skeleton.h"
#include "Animation/Skeleton.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_Skeleton)

UUE5StyleGuideRule_AssetNaming_Skeleton::UUE5StyleGuideRule_AssetNaming_Skeleton()
{
	RuleId = FName(TEXT("asset-naming-skeleton"));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-skeleton"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { USkeleton::StaticClass() };
	Prefix = TEXT("SKEL_");
}
