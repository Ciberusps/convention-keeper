// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperEditorCommands.h"

#define LOCTEXT_NAMESPACE "FConventionKeeperEditorModule"

void FConventionKeeperEditorCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "ConventionKeeper", "Validate convention folders", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(CoverageAction, "Convention Coverage", "Run rule coverage report; show results in Message Log", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(ComplianceAction, "Convention Compliance", "Run compliance report (covered assets passing validation); show results in Message Log", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
