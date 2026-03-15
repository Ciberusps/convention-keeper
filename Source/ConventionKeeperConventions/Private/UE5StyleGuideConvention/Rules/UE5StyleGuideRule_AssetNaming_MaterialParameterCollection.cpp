// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollection.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_MaterialParameterCollection)

UUE5StyleGuideRule_AssetNaming_MaterialParameterCollection::UUE5StyleGuideRule_AssetNaming_MaterialParameterCollection()
{
	RuleId = FName(TEXT("asset-naming-material-parameter-collection"));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-material-parameter-collection"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UMaterialParameterCollection::StaticClass() };
	Prefix = TEXT("MPC_");
}
