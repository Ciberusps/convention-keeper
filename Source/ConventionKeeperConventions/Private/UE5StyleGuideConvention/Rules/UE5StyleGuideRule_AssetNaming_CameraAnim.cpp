// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_CameraAnim.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_CameraAnim)

UUE5StyleGuideRule_AssetNaming_CameraAnim::UUE5StyleGuideRule_AssetNaming_CameraAnim()
{
	RuleId = FName(TEXT("asset-naming-camera-anim"));
	Description = FText::FromString(TEXT("Camera Anim assets must use prefix CA_ (UE5 Style Guide 1.2.7)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-camera-anim"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.CameraAnim"));
	Prefix = TEXT("CA_");
}
