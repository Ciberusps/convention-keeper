// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "Modules/ModuleInterface.h"

class FConventionKeeperValidationEditorModule final : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
