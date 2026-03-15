// Pavel Penkov 2025 All Rights Reserved.

#include "UHLConvention/Rules/UHLRule_FolderContent.h"

UUHLRule_FolderContent::UUHLRule_FolderContent()
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
