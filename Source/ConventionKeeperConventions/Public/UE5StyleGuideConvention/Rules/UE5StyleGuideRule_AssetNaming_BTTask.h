// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetRegistry/AssetData.h"

class IAssetRegistry;
#include "Rules/ConventionKeeperRule_AssetNaming.h"
#include "UE5StyleGuideRule_AssetNaming_BTTask.generated.h"

/** UE5 Style Guide 1.2.3: Behavior Tree Task (Blueprint) assets must use prefix BTTask_. Includes direct and indirect heirs. */
UCLASS()
class CONVENTIONKEEPERCONVENTIONS_API UUE5StyleGuideRule_AssetNaming_BTTask : public UConventionKeeperRule_AssetNaming
{
	GENERATED_BODY()

public:
	UUE5StyleGuideRule_AssetNaming_BTTask();

	virtual bool ShouldValidateAsset(const FAssetData& AssetData, IAssetRegistry* Registry = nullptr, const TMap<FString, FAssetData>* BlueprintByClassName = nullptr) const override;
};
