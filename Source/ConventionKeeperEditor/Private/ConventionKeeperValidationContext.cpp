// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperValidationContext.h"

#if WITH_EDITOR

namespace
{
	thread_local int32 GAssetValidationScopeDepth = 0;
	thread_local bool GPerAssetPackageValidationActive = false;
}

FConventionKeeperAssetValidationScope::FConventionKeeperAssetValidationScope(bool bEnable) : bEnabled(bEnable)
{
	if (bEnabled)
	{
		if (GAssetValidationScopeDepth++ == 0)
		{
			GPerAssetPackageValidationActive = true;
		}
	}
}

FConventionKeeperAssetValidationScope::~FConventionKeeperAssetValidationScope()
{
	if (bEnabled)
	{
		if (--GAssetValidationScopeDepth <= 0)
		{
			GAssetValidationScopeDepth = 0;
			GPerAssetPackageValidationActive = false;
		}
	}
}

bool FConventionKeeperAssetValidationScope::IsPerAssetPackageValidation()
{
	return GPerAssetPackageValidationActive;
}

#endif
