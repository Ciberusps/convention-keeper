// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperConvention/Rules/CKConventionRule_AssetNaming_CharacterAnimations.h"
#include "Animation/AnimSequence.h"

UCKConventionRule_AssetNaming_CharacterAnimations::UCKConventionRule_AssetNaming_CharacterAnimations()
{
	RuleId = FName(TEXT("asset-naming-character-animations"));
	Description = FText::FromString(TEXT("Animations in Content/{ProjectName}/Characters/{CharacterName}/Animations must be named AS_{CharacterName}_* with optional zero-padded number suffix (e.g. AS_Zombie_Jump_01)."));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}/Characters/{CharacterName}/Animations");
	AssetClasses = { UAnimSequence::StaticClass() };
	NamingTemplate = TEXT("AS_{CharacterName}_");
	NumberPaddingDigits = 2;
}
