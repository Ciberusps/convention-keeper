// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperConvention/ConventionKeeperConvention.h"
#include "ConventionKeeperConvention/Rules/CKConventionRule_AssetNaming_AnimSequence.h"
#include "ConventionKeeperConvention/Rules/CKConventionRule_FolderStructure_Content.h"
#include "ConventionKeeperConvention/Rules/CKConventionRule_FolderStructure_ProjectName.h"
#include "ConventionKeeperConvention/Rules/CKConventionRule_FolderStructure_Character.h"
#include "ConventionKeeperConvention/Rules/CKConventionRule_FolderStructure_CoreAI.h"
#include "ConventionKeeperConvention/Rules/CKConventionRule_AssetNaming_CharacterAnimations.h"
#include "Development/ConventionKeeperSettings.h"
#include "Internationalization/Text.h"
#include "UE5StyleGuideConvention/UE5StyleGuideConvention.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperConvention)

namespace
{
	static const TMap<FName, FString> GConventionKeeperConventionStrings_en = {
#include "ConventionKeeperConventionStrings_en.inl"
	};
	static const TMap<FName, FString> GConventionKeeperConventionStrings_ru = {
#include "ConventionKeeperConventionStrings_ru.inl"
	};
}

FText UConventionKeeperConvention::GetLocalizedRuleDescription(FName RuleId) const
{
	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	const FString Lang = Settings ? Settings->GetEffectiveLanguageCode() : TEXT("en");
	const TMap<FName, FString>* Map = Lang.StartsWith(TEXT("ru"), ESearchCase::IgnoreCase) ? &GConventionKeeperConventionStrings_ru : &GConventionKeeperConventionStrings_en;
	const FString* Str = Map->Find(RuleId);
	if (!Str)
	{
		const UConventionKeeperConvention_Base* Base = GetResolvedExtendsConvention();
		return Base ? Base->GetLocalizedRuleDescription(RuleId) : FText();
	}
	return FText::FromString(*Str);
}

UConventionKeeperConvention::UConventionKeeperConvention()
{
	Name = TEXT("Convention Keeper");
	Description = FText::FromString(TEXT("Default convention: UE5 Style Guide (v2) with AS_ for AnimSequence, plus folder structure and character animation naming. Extend for your project."));
	DocsLink = TEXT("https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file");

	ExtendsConvention = UUE5StyleGuideConvention::StaticClass();

	FRuleOverride AnimSeqOverride;
	AnimSeqOverride.RuleId = FName(TEXT("asset-naming-anim-sequence"));
	AnimSeqOverride.Mode = EConventionRuleOverrideMode::Replace;
	AnimSeqOverride.ReplacementRule = CreateDefaultSubobject<UCKConventionRule_AssetNaming_AnimSequence>(TEXT("Rule_AssetNaming_AnimSequence"));
	RuleOverrides.Add(AnimSeqOverride);

	Rules.Add(CreateDefaultSubobject<UCKConventionRule_FolderStructure_Content>(TEXT("Rule_FolderStructure_Content")));
	Rules.Add(CreateDefaultSubobject<UCKConventionRule_FolderStructure_ProjectName>(TEXT("Rule_FolderStructure_ProjectName")));
	Rules.Add(CreateDefaultSubobject<UCKConventionRule_FolderStructure_Character>(TEXT("Rule_FolderStructure_Character")));
	Rules.Add(CreateDefaultSubobject<UCKConventionRule_FolderStructure_CoreAI>(TEXT("Rule_FolderStructure_CoreAI")));
	Rules.Add(CreateDefaultSubobject<UCKConventionRule_AssetNaming_CharacterAnimations>(TEXT("Rule_AssetNaming_CharacterAnimations")));
}
