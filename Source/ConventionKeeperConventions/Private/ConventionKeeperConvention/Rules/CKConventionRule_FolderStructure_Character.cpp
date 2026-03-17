// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperConvention/Rules/CKConventionRule_FolderStructure_Character.h"

UCKConventionRule_FolderStructure_Character::UCKConventionRule_FolderStructure_Character()
{
	RuleId = FName(TEXT("folder-structure-character"));
	Description = FText::FromString(TEXT("Each character folder must have AI, Projectiles, Animations, Gyms, Data, Abilities, Materials."));
	FolderPath = FDirectoryPath(TEXT("Content/{ProjectName}/Characters/{CharacterName}/"));
	RequiredFolders = {
		FDirectoryPath(TEXT("Content/{ProjectName}/Characters/{CharacterName}/AI")),
		FDirectoryPath(TEXT("Content/{ProjectName}/Characters/{CharacterName}/Projectiles")),
		FDirectoryPath(TEXT("Content/{ProjectName}/Characters/{CharacterName}/Animations")),
		FDirectoryPath(TEXT("Content/{ProjectName}/Characters/{CharacterName}/Gyms")),
		FDirectoryPath(TEXT("Content/{ProjectName}/Characters/{CharacterName}/Data")),
		FDirectoryPath(TEXT("Content/{ProjectName}/Characters/{CharacterName}/Abilities")),
		FDirectoryPath(TEXT("Content/{ProjectName}/Characters/{CharacterName}/Materials")),
	};
}
