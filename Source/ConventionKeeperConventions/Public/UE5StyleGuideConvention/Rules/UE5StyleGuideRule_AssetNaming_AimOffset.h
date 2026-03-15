// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"
#include "UE5StyleGuideRule_AssetNaming_AimOffset.generated.h"

/** UE5 Style Guide 1.2.2: Aim Offset (1D and 2D) assets must use prefix AO_. */
UCLASS()
class CONVENTIONKEEPERCONVENTIONS_API UUE5StyleGuideRule_AssetNaming_AimOffset : public UConventionKeeperRule_AssetNaming
{
	GENERATED_BODY()

public:
	UUE5StyleGuideRule_AssetNaming_AimOffset();
};
