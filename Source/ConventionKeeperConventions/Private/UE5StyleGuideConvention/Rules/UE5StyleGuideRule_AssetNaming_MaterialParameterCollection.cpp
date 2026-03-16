// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollection.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_MaterialParameterCollection)

UUE5StyleGuideRule_AssetNaming_MaterialParameterCollection::UUE5StyleGuideRule_AssetNaming_MaterialParameterCollection()
{
	RuleId = FName(TEXT("asset-naming-material-parameter-collection"));
	Description = FText::FromString(TEXT("Material Parameter Collection assets must use prefix MPC_ (UE5 Style Guide 1.2.5)."));
	Description = FText::FromString(TEXT("Material Parameter Collection assets must use prefix MPC_ (UE5 Style Guide 1.2.5)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-material-parameter-collection"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UMaterialParameterCollection::StaticClass() };
	Prefix = TEXT("MPC_");
}
