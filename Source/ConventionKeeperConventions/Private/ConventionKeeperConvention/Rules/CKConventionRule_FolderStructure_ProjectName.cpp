// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperConvention/Rules/CKConventionRule_FolderStructure_ProjectName.h"

UCKConventionRule_FolderStructure_ProjectName::UCKConventionRule_FolderStructure_ProjectName()
{
	RuleId = FName(TEXT("folder-structure-project-name"));
	Description = FText::FromString(TEXT("Under Content/{ProjectName}/ require Characters, Maps, Core, SFX, VFX, AI."));
	FolderPath = FDirectoryPath(TEXT("Content/{ProjectName}/"));
	RequiredFolders = {
		FDirectoryPath(TEXT("Content/{ProjectName}/Characters")),
		FDirectoryPath(TEXT("Content/{ProjectName}/Maps")),
		FDirectoryPath(TEXT("Content/{ProjectName}/Core")),
		FDirectoryPath(TEXT("Content/{ProjectName}/SFX")),
		FDirectoryPath(TEXT("Content/{ProjectName}/VFX")),
		FDirectoryPath(TEXT("Content/{ProjectName}/AI")),
	};
}
