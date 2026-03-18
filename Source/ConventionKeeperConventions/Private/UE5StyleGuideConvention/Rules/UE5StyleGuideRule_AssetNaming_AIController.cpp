// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AIController.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_AIController)

UUE5StyleGuideRule_AssetNaming_AIController::UUE5StyleGuideRule_AssetNaming_AIController()
{
	RuleId = FName(TEXT("asset-naming-ai-controller"));
	Description = FText::FromString(TEXT("AI Controller (Blueprint) assets must use prefix AIC_ (UE5 Style Guide 1.2.3)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-ai-controller"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths = { TEXT("/Script/Engine.Blueprint") };
	Prefix = TEXT("AIC_");
	UConventionKeeperRule_AssetNaming::RegisterBlueprintSpecialtyNativePath(TEXT("/Script/Engine.AIController"));
}

bool UUE5StyleGuideRule_AssetNaming_AIController::ShouldValidateAsset(const FAssetData& AssetData, IAssetRegistry* Registry, const TMap<FString, FAssetData>* BlueprintByClassName) const
{
	if (!Registry || !BlueprintByClassName)
	{
		return false;
	}
	FString NativeRoot;
	return UConventionKeeperRule_AssetNaming::GetNativeParentClassPath(AssetData, *Registry, NativeRoot, BlueprintByClassName) &&
		UConventionKeeperRule_AssetNaming::NativeRootMatchesPath(NativeRoot, TEXT("/Script/Engine.AIController"));
}
