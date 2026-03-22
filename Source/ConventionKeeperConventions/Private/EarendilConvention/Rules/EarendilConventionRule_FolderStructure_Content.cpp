// Pavel Penkov 2025 All Rights Reserved.

#include "EarendilConvention/Rules/EarendilConventionRule_FolderStructure_Content.h"

UEarendilConventionRule_FolderStructure_Content::UEarendilConventionRule_FolderStructure_Content()
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
