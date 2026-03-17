// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_ParticleSystem.h"
#include "Particles/ParticleSystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_ParticleSystem)

UUE5StyleGuideRule_AssetNaming_ParticleSystem::UUE5StyleGuideRule_AssetNaming_ParticleSystem()
{
	RuleId = FName(TEXT("asset-naming-particle-system"));
	Description = FText::FromString(TEXT("Particle System (Cascade) and Niagara System assets must use prefix PS_ (UE5 Style Guide 1.2.12)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-particle-system"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClasses = { UParticleSystem::StaticClass() };
	AssetClassPaths.Add(TEXT("/Script/Niagara.NiagaraSystem"));
	Prefix = TEXT("PS_");
}
