// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Rules/ConventionKeeperRule_AssetPlacement.h"
#include "UE5StyleGuideRule_AssetPlacement_Maps.generated.h"

/** UE5 Style Guide 2.4: All Level/Map (World) assets must be in a folder named Maps. */
UCLASS()
class CONVENTIONKEEPERCONVENTIONS_API UUE5StyleGuideRule_AssetPlacement_Maps : public UConventionKeeperRule_AssetPlacement
{
	GENERATED_BODY()

public:
	UUE5StyleGuideRule_AssetPlacement_Maps();
};
