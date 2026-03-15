// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SkeletalMesh.h"
#include "Engine/SkeletalMesh.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_SkeletalMesh)

UUE5StyleGuideRule_AssetNaming_SkeletalMesh::UUE5StyleGuideRule_AssetNaming_SkeletalMesh()
{
	RuleId = FName(TEXT("asset-naming-skeletal-mesh"));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-skeletal-mesh"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { USkeletalMesh::StaticClass() };
	Prefix = TEXT("SK_");
}
