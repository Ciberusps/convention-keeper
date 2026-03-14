// Pavel Penkov 2025 All Rights Reserved.

#include "Conventions/UHLConvention/UHLConvention.h"
#include "Animation/AnimSequence.h"
#include "Internationalization/Text.h"
#include "NamingConventions/PascalCaseNamingConvention.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"
#include "Rules/ConventionKeeperRule_FolderStructure.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UHLConvention)

UUHLConvention::UUHLConvention()
{
	Name = "UHL Convention";
	NamingConvention = UPascalCaseNamingConvention::StaticClass();

	FDirectoryPath ContentFolderPath("Content/");
	// Should be added only if we have FMOD enabled
	TArray<FDirectoryPath> ContentRequiredFolders = {
		FDirectoryPath("Content/3rdParty/"),
		FDirectoryPath("Content/{ProjectName}/"),
		FDirectoryPath("Content/FMOD/"),
		FDirectoryPath("Content/Movies/")
	};
	{
		UConventionKeeperRule_FolderStructure* Rule = CreateDefaultSubobject<UConventionKeeperRule_FolderStructure>(TEXT("Rule_Content"));
		Rule->RuleId = FName(TEXT("folder-content"));
		Rule->Description = FText::FromString(TEXT("Root Content folder must contain 3rdParty, {ProjectName}, FMOD, Movies."));
		Rule->FolderPath = ContentFolderPath;
		Rule->RequiredFolders = ContentRequiredFolders;
		Rules.Add(Rule);
	}

	FDirectoryPath ProjectNameFolderPath("Content/{ProjectName}/");
	TArray<FDirectoryPath> ProjectNameRequiredFolders = {
		FDirectoryPath("Content/{ProjectName}/Characters"),
		FDirectoryPath("Content/{ProjectName}/Maps"),
		FDirectoryPath("Content/{ProjectName}/Core"),
		FDirectoryPath("Content/{ProjectName}/SFX"),
		FDirectoryPath("Content/{ProjectName}/VFX"),
		FDirectoryPath("Content/{ProjectName}/AI")
	};
	{
		UConventionKeeperRule_FolderStructure* Rule = CreateDefaultSubobject<UConventionKeeperRule_FolderStructure>(TEXT("Rule_ProjectName"));
		Rule->RuleId = FName(TEXT("folder-project-name"));
		Rule->Description = FText::FromString(TEXT("Under Content/{ProjectName}/ require Characters, Maps, Core, SFX, VFX, AI."));
		Rule->FolderPath = ProjectNameFolderPath;
		Rule->RequiredFolders = ProjectNameRequiredFolders;
		Rules.Add(Rule);
	}

	FDirectoryPath CharacterFolderPath("Content/{ProjectName}/Characters/{CharacterName}/");
	TArray<FDirectoryPath> CharacterRequiredFolders = {
		FDirectoryPath("Content/{ProjectName}/Characters/{CharacterName}/AI"),
		FDirectoryPath("Content/{ProjectName}/Characters/{CharacterName}/Projectiles"),
		FDirectoryPath("Content/{ProjectName}/Characters/{CharacterName}/Animations"),
		FDirectoryPath("Content/{ProjectName}/Characters/{CharacterName}/Gyms"),
		FDirectoryPath("Content/{ProjectName}/Characters/{CharacterName}/Data"),
		FDirectoryPath("Content/{ProjectName}/Characters/{CharacterName}/Abilities"),
		FDirectoryPath("Content/{ProjectName}/Characters/{CharacterName}/Materials")
	};
	{
		UConventionKeeperRule_FolderStructure* Rule = CreateDefaultSubobject<UConventionKeeperRule_FolderStructure>(TEXT("Rule_Character"));
		Rule->RuleId = FName(TEXT("folder-character"));
		Rule->Description = FText::FromString(TEXT("Each character folder must have AI, Projectiles, Animations, Gyms, Data, Abilities, Materials."));
		Rule->FolderPath = CharacterFolderPath;
		Rule->RequiredFolders = CharacterRequiredFolders;
		Rules.Add(Rule);
	}

	FDirectoryPath CoreFolderPath("Content/{ProjectName}/Core/AI/");
	{
		UConventionKeeperRule_FolderStructure* Rule = CreateDefaultSubobject<UConventionKeeperRule_FolderStructure>(TEXT("Rule_CoreAI"));
		Rule->RuleId = FName(TEXT("folder-core-ai"));
		Rule->Description = FText::FromString(TEXT("Content/{ProjectName}/Core/AI/ must exist."));
		Rule->FolderPath = CoreFolderPath;
		Rules.Add(Rule);
	}

	{
		UConventionKeeperRule_AssetNaming* Rule = CreateDefaultSubobject<UConventionKeeperRule_AssetNaming>(TEXT("Rule_CharacterAnimNaming"));
		Rule->RuleId = FName(TEXT("asset-naming-character-animations"));
		Rule->Description = FText::FromString(TEXT("Animations in Content/{ProjectName}/Characters/{CharacterName}/Animations must be named AS_{CharacterName}_* with optional zero-padded number suffix (e.g. AS_Zombie_Jump_01)."));
		Rule->FolderPathPattern.Path = TEXT("Content/{ProjectName}/Characters/{CharacterName}/Animations");
		Rule->AssetClasses = { UAnimSequence::StaticClass() };
		Rule->NamingTemplate = TEXT("AS_{CharacterName}_");
		Rule->NumberPaddingDigits = 2;
		Rules.Add(Rule);
	}
}
