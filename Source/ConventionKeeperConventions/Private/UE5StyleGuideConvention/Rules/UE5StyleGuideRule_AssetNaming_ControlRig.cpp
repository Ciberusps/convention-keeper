// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_ControlRig.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_ControlRig)

UUE5StyleGuideRule_AssetNaming_ControlRig::UUE5StyleGuideRule_AssetNaming_ControlRig()
{
	RuleId = FName(TEXT("asset-naming-control-rig"));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-control-rig"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths = { TEXT("/Script/ControlRigDeveloper.ControlRigBlueprint") };
	AllowedPrefixes = { TEXT("CR_"), TEXT("Rig_") };
}
