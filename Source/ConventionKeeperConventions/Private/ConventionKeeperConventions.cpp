// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperConventions.h"

#include "ConventionKeeperConvention/ConventionKeeperConvention.h"
#include "Development/ConventionKeeperSettings.h"

IMPLEMENT_MODULE(FConventionKeeperConventionsModule, ConventionKeeperConventions)

void FConventionKeeperConventionsModule::StartupModule()
{
	UConventionKeeperSettings* Settings = GetMutableDefault<UConventionKeeperSettings>();
	if (Settings && !Settings->Convention)
	{
		Settings->Convention = UConventionKeeperConvention::StaticClass();
	}
}

void FConventionKeeperConventionsModule::ShutdownModule()
{
}
