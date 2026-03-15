// Pavel Penkov 2025 All Rights Reserved.

#include "UHLConvention/UHLConvention.h"
#include "Development/ConventionKeeperSettings.h"
#include "Internationalization/Text.h"
#include "NamingConventions/PascalCaseNamingConvention.h"
#include "UHLConvention/Rules/UHLRule_AssetNamingCharacterAnimations.h"
#include "UHLConvention/Rules/UHLRule_FolderContent.h"
#include "UHLConvention/Rules/UHLRule_FolderCharacter.h"
#include "UHLConvention/Rules/UHLRule_FolderCoreAI.h"
#include "UHLConvention/Rules/UHLRule_FolderProjectName.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UHLConvention)

namespace
{
	static const TMap<FName, FString> GUHLConventionStrings_en = {
#include "UHLConventionStrings_en.inl"
	};
	static const TMap<FName, FString> GUHLConventionStrings_ru = {
#include "UHLConventionStrings_ru.inl"
	};
}

FText UUHLConvention::GetLocalizedRuleDescription(FName RuleId) const
{
	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	const FString Lang = Settings ? Settings->GetEffectiveLanguageCode() : TEXT("en");
	const TMap<FName, FString>* Map = Lang.StartsWith(TEXT("ru"), ESearchCase::IgnoreCase) ? &GUHLConventionStrings_ru : &GUHLConventionStrings_en;
	const FString* Str = Map->Find(RuleId);
	if (!Str)
	{
		return FText();
	}
	return FText::FromString(*Str);
}

UUHLConvention::UUHLConvention()
{
	Name = "UHL Convention";
	NamingConvention = UPascalCaseNamingConvention::StaticClass();

	Rules.Add(CreateDefaultSubobject<UUHLRule_FolderContent>(TEXT("Rule_Content")));
	Rules.Add(CreateDefaultSubobject<UUHLRule_FolderProjectName>(TEXT("Rule_ProjectName")));
	Rules.Add(CreateDefaultSubobject<UUHLRule_FolderCharacter>(TEXT("Rule_Character")));
	Rules.Add(CreateDefaultSubobject<UUHLRule_FolderCoreAI>(TEXT("Rule_CoreAI")));
	Rules.Add(CreateDefaultSubobject<UUHLRule_AssetNamingCharacterAnimations>(TEXT("Rule_CharacterAnimNaming")));
}
