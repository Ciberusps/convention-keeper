// Pavel Penkov 2025 All Rights Reserved.

#include "EarendilConvention/Rules/EarendilConventionRule_FolderStructure_CharacterGyms.h"

UEarendilConventionRule_FolderStructure_CharacterGyms::UEarendilConventionRule_FolderStructure_CharacterGyms()
{
	RuleId = FName(TEXT("folder-structure-character-gyms"));
	Description = FText::FromString(TEXT("Character Gyms folder must contain Gym, AIGym, AIGym arena, and AnimGym level assets per character."));
	FolderPath = FDirectoryPath(TEXT("Content/{ProjectName}/Characters/{CharacterName}/Gyms/"));
	RequiredAssets = {
		TEXT("Gym_{CharacterName}"),
		TEXT("AIGym_{CharacterName}"),
		TEXT("AIGym_{CharacterName}_Arena"),
		TEXT("AnimGym_{CharacterName}"),
	};
	bOtherAssetsNotAllowed = true;
}
