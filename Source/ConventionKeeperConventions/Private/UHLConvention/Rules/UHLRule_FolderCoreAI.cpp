// Pavel Penkov 2025 All Rights Reserved.

#include "UHLConvention/Rules/UHLRule_FolderCoreAI.h"

UUHLRule_FolderCoreAI::UUHLRule_FolderCoreAI()
{
	RuleId = FName(TEXT("folder-structure-core-ai"));
	Description = FText::FromString(TEXT("Content/{ProjectName}/Core/AI/ must exist."));
	FolderPath = FDirectoryPath(TEXT("Content/{ProjectName}/Core/AI/"));
}
