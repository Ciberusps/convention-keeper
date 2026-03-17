// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_DestructibleMesh.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_DestructibleMesh)

UUE5StyleGuideRule_AssetNaming_DestructibleMesh::UUE5StyleGuideRule_AssetNaming_DestructibleMesh()
{
	RuleId = FName(TEXT("asset-naming-destructible-mesh"));
	Description = FText::FromString(TEXT("Destructible Mesh (legacy Apex) must use prefix DM_ (UE5 Style Guide 1.2.9)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-destructible-mesh"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/ApexDestruction.DestructibleMesh"));
	Prefix = TEXT("DM_");
}
