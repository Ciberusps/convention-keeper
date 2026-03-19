// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_StaticMesh.h"
#include "Engine/StaticMesh.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_StaticMesh)

UUE5StyleGuideRule_AssetNaming_StaticMesh::UUE5StyleGuideRule_AssetNaming_StaticMesh()
{
	RuleId = FName(TEXT("asset-naming-static-mesh"));
	Description = FText::FromString(TEXT("Static Mesh assets must use prefix S_ (UE5 Style Guide 1.2.1 Most Common)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-static-mesh"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UStaticMesh::StaticClass() };
	Prefix = TEXT("S_");
}
