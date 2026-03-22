// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#if WITH_EDITOR

/** True while ValidateData runs with asset package paths (on-save / validate selection). Folder rules can opt out via bValidateOnPerAssetSave. */
struct CONVENTIONKEEPEREDITOR_API FConventionKeeperAssetValidationScope
{
	explicit FConventionKeeperAssetValidationScope(bool bEnable);
	~FConventionKeeperAssetValidationScope();

	FConventionKeeperAssetValidationScope(const FConventionKeeperAssetValidationScope&) = delete;
	FConventionKeeperAssetValidationScope& operator=(const FConventionKeeperAssetValidationScope&) = delete;

	static bool IsPerAssetPackageValidation();

private:
	const bool bEnabled = false;
};

#endif
