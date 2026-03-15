// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperConventions.h"
#include "Development/ConventionKeeperSettings.h"
#include "UHLConvention/UHLConvention.h"

IMPLEMENT_MODULE(FConventionKeeperConventionsModule, ConventionKeeperConventions)

void FConventionKeeperConventionsModule::StartupModule()
{
	UConventionKeeperSettings* Settings = GetMutableDefault<UConventionKeeperSettings>();
	if (Settings && !Settings->Convention)
	{
		Settings->Convention = UUHLConvention::StaticClass();
	}
}

void FConventionKeeperConventionsModule::ShutdownModule()
{
}
