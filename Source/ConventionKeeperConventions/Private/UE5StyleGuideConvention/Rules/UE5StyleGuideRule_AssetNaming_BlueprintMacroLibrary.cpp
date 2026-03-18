// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BlueprintMacroLibrary.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_BlueprintMacroLibrary)

UUE5StyleGuideRule_AssetNaming_BlueprintMacroLibrary::UUE5StyleGuideRule_AssetNaming_BlueprintMacroLibrary()
{
	RuleId = FName(TEXT("asset-naming-blueprint-macro-library"));
	Description = FText::FromString(TEXT("Blueprint Macro Library assets must use prefix BPML_ (UE5 Style Guide 1.2.4)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-blueprint-macro-library"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths.Add(TEXT("/Script/Engine.Blueprint"));
	Prefix = TEXT("BPML_");
}

bool UUE5StyleGuideRule_AssetNaming_BlueprintMacroLibrary::ShouldValidateAsset(const FAssetData& AssetData, IAssetRegistry* Registry, const TMap<FString, FAssetData>* BlueprintByClassName) const
{
	if (!Registry || !BlueprintByClassName)
	{
		return false;
	}
	FString NativeRoot;
	return UConventionKeeperRule_AssetNaming::GetNativeParentClassPath(AssetData, *Registry, NativeRoot, BlueprintByClassName) &&
		UConventionKeeperRule_AssetNaming::NativeRootMatchesPath(NativeRoot, TEXT("/Script/Engine.BlueprintMacroLibrary"));
}
