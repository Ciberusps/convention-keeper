// Pavel Penkov 2025 All Rights Reserved.

#include "EarendilConvention/Rules/EarendilConventionRule_FolderStructure_CoreAI.h"

UEarendilConventionRule_FolderStructure_CoreAI::UEarendilConventionRule_FolderStructure_CoreAI()
{
	RuleId = FName(TEXT("folder-structure-core-ai"));
	Description = FText::FromString(TEXT("Content/{ProjectName}/Core/AI/ must exist."));
	FolderPath = FDirectoryPath(TEXT("Content/{ProjectName}/Core/AI/"));
}
