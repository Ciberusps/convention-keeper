// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_StaticVectorField.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_StaticVectorField)

UUE5StyleGuideRule_AssetNaming_StaticVectorField::UUE5StyleGuideRule_AssetNaming_StaticVectorField()
{
	RuleId = FName(TEXT("asset-naming-static-vector-field"));
	Description = FText::FromString(TEXT("Static Vector Field assets must use prefix VF_ (UE5 Style Guide 1.2.7)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-static-vector-field"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.VectorFieldStatic"));
	Prefix = TEXT("VF_");
}
