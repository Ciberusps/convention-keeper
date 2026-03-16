// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"
#include "UE5StyleGuideRule_AssetNaming_Texture.generated.h"

/** UE5 Style Guide 1.2.6: Texture assets must use prefix T_, TC_, MT_, RT_, RTC_, or TLP_ by type; T_ textures may have optional suffix _D, _N, _R, etc. (one or more of D,N,R,A,O,B,E,M,S). */
UCLASS()
class CONVENTIONKEEPERCONVENTIONS_API UUE5StyleGuideRule_AssetNaming_Texture : public UConventionKeeperRule_AssetNaming
{
	GENERATED_BODY()

public:
	UUE5StyleGuideRule_AssetNaming_Texture();

	virtual bool GetRequiredPrefixForAsset(const FAssetData& AssetData, FString& OutPrefix) const override;
	virtual bool GetCustomSuffixValidity(const FString& AssetName, const FString& UsedPrefix, bool& OutValid) const override;
	virtual FText GetCustomSuffixFailureMessage(const FString& AssetName, const FString& UsedPrefix) const override;
};
