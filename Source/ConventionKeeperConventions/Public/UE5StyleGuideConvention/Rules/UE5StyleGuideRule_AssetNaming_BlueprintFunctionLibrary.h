// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetRegistry/AssetData.h"

class IAssetRegistry;
#include "Rules/ConventionKeeperRule_AssetNaming.h"
#include "UE5StyleGuideRule_AssetNaming_BlueprintFunctionLibrary.generated.h"

/** UE5 Style Guide 1.2.4: Blueprint Function Library assets must use prefix BPFL_. Includes direct and indirect (Blueprint child) heirs of BlueprintFunctionLibrary. */
UCLASS()
class CONVENTIONKEEPERCONVENTIONS_API UUE5StyleGuideRule_AssetNaming_BlueprintFunctionLibrary : public UConventionKeeperRule_AssetNaming
{
	GENERATED_BODY()

public:
	UUE5StyleGuideRule_AssetNaming_BlueprintFunctionLibrary();

	virtual bool ShouldValidateAsset(const FAssetData& AssetData, IAssetRegistry* Registry = nullptr, const TMap<FString, FAssetData>* BlueprintByClassName = nullptr) const override;
};
