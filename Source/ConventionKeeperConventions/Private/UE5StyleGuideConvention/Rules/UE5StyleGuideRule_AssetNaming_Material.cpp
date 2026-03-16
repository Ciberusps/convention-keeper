// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Material.h"
#include "Materials/Material.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_Material)

UUE5StyleGuideRule_AssetNaming_Material::UUE5StyleGuideRule_AssetNaming_Material()
{
	RuleId = FName(TEXT("asset-naming-material"));
	Description = FText::FromString(TEXT("Material assets must use prefix M_ (Surface) or PP_ (Post Process) by Material Domain (UE5 Style Guide 1.2.5)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-material"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UMaterial::StaticClass() };
}

bool UUE5StyleGuideRule_AssetNaming_Material::GetRequiredPrefixForAsset(const FAssetData& AssetData, FString& OutPrefix) const
{
	UObject* Loaded = AssetData.GetAsset();
	UMaterial* Material = Cast<UMaterial>(Loaded);
	if (!Material)
	{
		return false;
	}
	if (Material->MaterialDomain == EMaterialDomain::MD_PostProcess)
	{
		OutPrefix = TEXT("PP_");
	}
	else
	{
		OutPrefix = TEXT("M_");
	}
	return true;
}
