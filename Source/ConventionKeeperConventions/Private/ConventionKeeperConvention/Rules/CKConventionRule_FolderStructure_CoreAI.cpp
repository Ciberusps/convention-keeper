// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperConvention/Rules/CKConventionRule_FolderStructure_CoreAI.h"

UCKConventionRule_FolderStructure_CoreAI::UCKConventionRule_FolderStructure_CoreAI()
{
	RuleId = FName(TEXT("folder-structure-core-ai"));
	Description = FText::FromString(TEXT("Content/{ProjectName}/Core/AI/ must exist."));
	FolderPath = FDirectoryPath(TEXT("Content/{ProjectName}/Core/AI/"));
}
