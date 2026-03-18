// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BTService.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_BTService)

UUE5StyleGuideRule_AssetNaming_BTService::UUE5StyleGuideRule_AssetNaming_BTService()
{
	RuleId = FName(TEXT("asset-naming-bt-service"));
	Description = FText::FromString(TEXT("Behavior Tree Service (Blueprint) assets must use prefix BTService_ (UE5 Style Guide 1.2.3)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-bt-service"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths = { TEXT("/Script/Engine.Blueprint") };
	Prefix = TEXT("BTService_");
	UConventionKeeperRule_AssetNaming::RegisterBlueprintSpecialtyNativePath(TEXT("/Script/AIModule.BTService_BlueprintBase"));
}

bool UUE5StyleGuideRule_AssetNaming_BTService::ShouldValidateAsset(const FAssetData& AssetData, IAssetRegistry* Registry, const TMap<FString, FAssetData>* BlueprintByClassName) const
{
	if (!Registry || !BlueprintByClassName)
	{
		return false;
	}
	FString NativeRoot;
	return UConventionKeeperRule_AssetNaming::GetNativeParentClassPath(AssetData, *Registry, NativeRoot, BlueprintByClassName) &&
		UConventionKeeperRule_AssetNaming::NativeRootMatchesPath(NativeRoot, TEXT("/Script/AIModule.BTService_BlueprintBase"));
}
