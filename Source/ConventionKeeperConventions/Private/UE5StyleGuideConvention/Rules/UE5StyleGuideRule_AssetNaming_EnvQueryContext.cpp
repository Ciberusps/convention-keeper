// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_EnvQueryContext.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_EnvQueryContext)

UUE5StyleGuideRule_AssetNaming_EnvQueryContext::UUE5StyleGuideRule_AssetNaming_EnvQueryContext()
{
	RuleId = FName(TEXT("asset-naming-env-query-context"));
	Description = FText::FromString(TEXT("Env Query Context (Blueprint) assets must use prefix EQS_ and suffix Context (UE5 Style Guide 1.2.3)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-env-query-context"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths = { TEXT("/Script/Engine.Blueprint") };
	Prefix = TEXT("EQS_");
	Suffix = TEXT("Context");
}

bool UUE5StyleGuideRule_AssetNaming_EnvQueryContext::ShouldValidateAsset(const FAssetData& AssetData, IAssetRegistry* Registry, const TMap<FString, FAssetData>* BlueprintByClassName) const
{
	if (!Registry || !BlueprintByClassName)
	{
		return false;
	}
	FString NativeRoot;
	return UConventionKeeperRule_AssetNaming::GetNativeParentClassPath(AssetData, *Registry, NativeRoot, BlueprintByClassName) &&
		UConventionKeeperRule_AssetNaming::NativeRootMatchesPath(NativeRoot, TEXT("/Script/AIModule.EnvQueryContext"));
}
