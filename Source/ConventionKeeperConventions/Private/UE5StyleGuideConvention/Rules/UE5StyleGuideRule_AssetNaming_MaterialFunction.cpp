// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MaterialFunction.h"
#include "Materials/MaterialFunction.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_MaterialFunction)

UUE5StyleGuideRule_AssetNaming_MaterialFunction::UUE5StyleGuideRule_AssetNaming_MaterialFunction()
{
	RuleId = FName(TEXT("asset-naming-material-function"));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-material-function"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UMaterialFunction::StaticClass() };
	Prefix = TEXT("MF_");
}
