// Pavel Penkov 2025 All Rights Reserved.

#include "UHLConvention/Rules/UHLRule_AssetNamingCharacterAnimations.h"
#include "Animation/AnimSequence.h"

UUHLRule_AssetNamingCharacterAnimations::UUHLRule_AssetNamingCharacterAnimations()
{
	RuleId = FName(TEXT("asset-naming-character-animations"));
	Description = FText::FromString(TEXT("Animations in Content/{ProjectName}/Characters/{CharacterName}/Animations must be named AS_{CharacterName}_* with optional zero-padded number suffix (e.g. AS_Zombie_Jump_01)."));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}/Characters/{CharacterName}/Animations");
	AssetClasses = { UAnimSequence::StaticClass() };
	NamingTemplate = TEXT("AS_{CharacterName}_");
	NumberPaddingDigits = 2;
}
