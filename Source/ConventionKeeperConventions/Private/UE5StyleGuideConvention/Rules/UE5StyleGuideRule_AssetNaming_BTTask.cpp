// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BTTask.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_BTTask)

UUE5StyleGuideRule_AssetNaming_BTTask::UUE5StyleGuideRule_AssetNaming_BTTask()
{
	RuleId = FName(TEXT("asset-naming-bt-task"));
	Description = FText::FromString(TEXT("Behavior Tree Task (Blueprint) assets must use prefix BTTask_ (UE5 Style Guide 1.2.3)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-bt-task"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths = { TEXT("/Script/Engine.Blueprint") };
	Prefix = TEXT("BTTask_");
}

bool UUE5StyleGuideRule_AssetNaming_BTTask::ShouldValidateAsset(const FAssetData& AssetData, IAssetRegistry* Registry, const TMap<FString, FAssetData>* BlueprintByClassName) const
{
	if (!Registry || !BlueprintByClassName)
	{
		return false;
	}
	FString NativeRoot;
	return UConventionKeeperRule_AssetNaming::GetNativeParentClassPath(AssetData, *Registry, NativeRoot, BlueprintByClassName) &&
		UConventionKeeperRule_AssetNaming::NativeRootMatchesPath(NativeRoot, TEXT("/Script/AIModule.BTTask_BlueprintBase"));
}
