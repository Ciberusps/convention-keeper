// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"
#include "UE5StyleGuideRule_AssetNaming_SkeletalMesh.generated.h"

/** UE5 Style Guide 1.2.2: Skeletal Mesh assets must use prefix SK_. */
UCLASS()
class CONVENTIONKEEPERCONVENTIONS_API UUE5StyleGuideRule_AssetNaming_SkeletalMesh : public UConventionKeeperRule_AssetNaming
{
	GENERATED_BODY()

public:
	UUE5StyleGuideRule_AssetNaming_SkeletalMesh();
};
