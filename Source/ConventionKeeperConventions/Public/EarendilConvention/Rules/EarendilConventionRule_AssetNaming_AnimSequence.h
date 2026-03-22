// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"
#include "EarendilConventionRule_AssetNaming_AnimSequence.generated.h"

/** EarendilConvention override: Animation Sequence uses prefix AS_ (not A_ as in UE5 Style Guide). */
UCLASS()
class CONVENTIONKEEPERCONVENTIONS_API UEarendilConventionRule_AssetNaming_AnimSequence : public UConventionKeeperRule_AssetNaming
{
	GENERATED_BODY()

public:
	UEarendilConventionRule_AssetNaming_AnimSequence();
};
