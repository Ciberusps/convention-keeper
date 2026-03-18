// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AnimatedVectorField.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_AnimatedVectorField)

UUE5StyleGuideRule_AssetNaming_AnimatedVectorField::UUE5StyleGuideRule_AssetNaming_AnimatedVectorField()
{
	RuleId = FName(TEXT("asset-naming-animated-vector-field"));
	Description = FText::FromString(TEXT("Animated Vector Field assets must use prefix VFA_ (UE5 Style Guide 1.2.7)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-animated-vector-field"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.VectorFieldAnimated"));
	Prefix = TEXT("VFA_");
}
