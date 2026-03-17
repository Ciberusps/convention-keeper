// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"
#include "UE5StyleGuideRule_AssetNaming_DestructibleMesh.generated.h"

/**
 * UE5 Style Guide 1.2.9: Destructible Mesh (legacy Apex Destruction) must use prefix DM_.
 * In UE5, Chaos destruction uses Geometry Collection assets; this rule applies to the legacy
 * Destructible Mesh asset type from the Apex Destruction plugin when present.
 */
UCLASS()
class CONVENTIONKEEPERCONVENTIONS_API UUE5StyleGuideRule_AssetNaming_DestructibleMesh : public UConventionKeeperRule_AssetNaming
{
	GENERATED_BODY()

public:
	UUE5StyleGuideRule_AssetNaming_DestructibleMesh();
};
