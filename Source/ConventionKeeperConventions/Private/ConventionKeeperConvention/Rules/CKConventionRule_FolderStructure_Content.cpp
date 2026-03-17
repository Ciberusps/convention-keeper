// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperConvention/Rules/CKConventionRule_FolderStructure_Content.h"

UCKConventionRule_FolderStructure_Content::UCKConventionRule_FolderStructure_Content()
{
	RuleId = FName(TEXT("folder-structure-content"));
	Description = FText::FromString(TEXT("Root Content folder must contain 3rdParty, {ProjectName}, FMOD, Movies."));
	FolderPath = FDirectoryPath(TEXT("Content/"));
	RequiredFolders = {
		FDirectoryPath(TEXT("Content/3rdParty/")),
		FDirectoryPath(TEXT("Content/{ProjectName}/")),
		FDirectoryPath(TEXT("Content/FMOD/")),
		FDirectoryPath(TEXT("Content/Movies/")),
		FDirectoryPath(TEXT("Content/Developers/")),
		FDirectoryPath(TEXT("Content/Splash/")),
	};
	bOtherFoldersNotAllowed = true;
}
