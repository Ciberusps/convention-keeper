// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Texture.h"
#include "Engine/Texture2D.h"
#include "Localization/ConventionKeeperLocalization.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_Texture)

namespace
{
	const TCHAR* AllowedTextureSuffixLetters = TEXT("DNRABOEMS");

	bool IsTextureSuffixValid(const FString& AssetName, const FString& Prefix)
	{
		if (!AssetName.StartsWith(Prefix))
		{
			return true;
		}
		FString AfterPrefix = AssetName.Mid(Prefix.Len());
		if (AfterPrefix.IsEmpty())
		{
			return false;
		}
		int32 LastUnderscore = INDEX_NONE;
		if (!AfterPrefix.FindLastChar(TEXT('_'), LastUnderscore))
		{
			return true;
		}
		FString SuffixSegment = AfterPrefix.Mid(LastUnderscore + 1);
		if (SuffixSegment.IsEmpty())
		{
			return true;
		}
		for (TCHAR C : SuffixSegment)
		{
			if (FCString::Strchr(AllowedTextureSuffixLetters, C) == nullptr)
			{
				return false;
			}
		}
		return true;
	}
}

UUE5StyleGuideRule_AssetNaming_Texture::UUE5StyleGuideRule_AssetNaming_Texture()
{
	RuleId = FName(TEXT("asset-naming-texture"));
	Description = FText::FromString(TEXT("Texture assets must use prefix T_, TC_, MT_, RT_, RTC_, or TLP_ by type; T_ textures may have optional suffix _D, _N, _R, etc. (UE5 Style Guide 1.2.6)."));
	Description = FText::FromString(TEXT("Texture assets must use prefix T_, TC_, MT_, RT_, RTC_, or TLP_ by type; T_ textures may have optional suffix _D, _N, _R, etc. (UE5 Style Guide 1.2.6)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-texture"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UTexture2D::StaticClass() };
	AssetClassPaths.Add(TEXT("/Script/Engine.TextureCube"));
	AssetClassPaths.Add(TEXT("/Script/Engine.TextureRenderTarget2D"));
	AssetClassPaths.Add(TEXT("/Script/Engine.TextureRenderTargetCube"));
	AssetClassPaths.Add(TEXT("/Script/Engine.TextureLightProfile"));
	AssetClassPaths.Add(TEXT("/Script/MediaAssets.MediaTexture"));
}

bool UUE5StyleGuideRule_AssetNaming_Texture::GetRequiredPrefixForAsset(const FAssetData& AssetData, FString& OutPrefix) const
{
	UObject* Loaded = AssetData.GetAsset();
	if (!Loaded)
	{
		return false;
	}
	FString ClassName = Loaded->GetClass()->GetName();
	if (ClassName == TEXT("TextureCube"))
	{
		OutPrefix = TEXT("TC_");
		return true;
	}
	if (ClassName == TEXT("TextureRenderTarget2D"))
	{
		OutPrefix = TEXT("RT_");
		return true;
	}
	if (ClassName == TEXT("TextureRenderTargetCube"))
	{
		OutPrefix = TEXT("RTC_");
		return true;
	}
	if (ClassName == TEXT("TextureLightProfile"))
	{
		OutPrefix = TEXT("TLP_");
		return true;
	}
	if (ClassName == TEXT("MediaTexture"))
	{
		OutPrefix = TEXT("MT_");
		return true;
	}
	if (ClassName == TEXT("Texture2D"))
	{
		OutPrefix = TEXT("T_");
		return true;
	}
	return false;
}

bool UUE5StyleGuideRule_AssetNaming_Texture::GetCustomSuffixValidity(const FString& AssetName, const FString& UsedPrefix, bool& OutValid) const
{
	if (UsedPrefix != TEXT("T_"))
	{
		return false;
	}
	OutValid = IsTextureSuffixValid(AssetName, UsedPrefix);
	return true;
}

FText UUE5StyleGuideRule_AssetNaming_Texture::GetCustomSuffixFailureMessage(const FString& AssetName, const FString& UsedPrefix) const
{
	if (UsedPrefix != TEXT("T_"))
	{
		return FText();
	}
	return ConventionKeeperLoc::GetText(FName(TEXT("AssetNamingTextureSuffixLetters")));
}
