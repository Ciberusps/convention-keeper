// Pavel Penkov 2025 All Rights Reserved.

#include "EarendilConvention/EarendilConvention.h"
#include "EarendilConvention/Rules/EarendilConventionRule_AssetNaming_AnimSequence.h"
#include "EarendilConvention/Rules/EarendilConventionRule_FolderStructure_Content.h"
#include "EarendilConvention/Rules/EarendilConventionRule_FolderStructure_ProjectName.h"
#include "EarendilConvention/Rules/EarendilConventionRule_FolderStructure_Character.h"
#include "EarendilConvention/Rules/EarendilConventionRule_FolderStructure_CoreAI.h"
#include "EarendilConvention/Rules/EarendilConventionRule_AssetNaming_CharacterAnimations.h"
#include "EarendilConvention/Rules/EarendilConventionRule_AssetNaming_StateTree.h"
#include "Development/ConventionKeeperSettings.h"
#include "Internationalization/Text.h"
#include "UE5StyleGuideConvention/UE5StyleGuideConvention.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(EarendilConvention)

namespace
{
	static const TMap<FName, FString> GEarendilConventionStrings_en = {
#include "EarendilConventionStrings_en.inl"
	};
	static const TMap<FName, FString> GEarendilConventionStrings_ru = {
#include "EarendilConventionStrings_ru.inl"
	};
}

FText UEarendilConvention::GetLocalizedRuleDescription(FName RuleId) const
{
	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	const FString Lang = Settings ? Settings->GetEffectiveLanguageCode() : TEXT("en");
	const TMap<FName, FString>* Map = Lang.StartsWith(TEXT("ru"), ESearchCase::IgnoreCase) ? &GEarendilConventionStrings_ru : &GEarendilConventionStrings_en;
	const FString* Str = Map->Find(RuleId);
	if (!Str)
	{
		const UConventionKeeperConvention_Base* Base = GetResolvedExtendsConvention();
		return Base ? Base->GetLocalizedRuleDescription(RuleId) : FText();
	}
	return FText::FromString(*Str);
}

UEarendilConvention::UEarendilConvention()
{
	Name = TEXT("earendil-convention");
	Description = FText::FromString(
		TEXT("Extends UE5 Style Guide with project folder rules, AnimSequence AS_ override, character animation and StateTree naming. Documentation: Docs/Conventions/earendil-convention.md (Name = doc slug)."));

	ExtendsConvention = UUE5StyleGuideConvention::StaticClass();

	FRuleOverride AnimSeqOverride;
	AnimSeqOverride.RuleId = FName(TEXT("asset-naming-anim-sequence")); // parent UE5StyleGuide rule id to replace
	AnimSeqOverride.Mode = EConventionRuleOverrideMode::Replace;
	AnimSeqOverride.ReplacementRule = CreateDefaultSubobject<UEarendilConventionRule_AssetNaming_AnimSequence>(TEXT("Rule_AssetNaming_AnimSequence"));
	RuleOverrides.Add(AnimSeqOverride);

	Rules.Add(CreateDefaultSubobject<UEarendilConventionRule_FolderStructure_Content>(TEXT("Rule_FolderStructure_Content")));
	Rules.Add(CreateDefaultSubobject<UEarendilConventionRule_FolderStructure_ProjectName>(TEXT("Rule_FolderStructure_ProjectName")));
	Rules.Add(CreateDefaultSubobject<UEarendilConventionRule_FolderStructure_Character>(TEXT("Rule_FolderStructure_Character")));
	Rules.Add(CreateDefaultSubobject<UEarendilConventionRule_FolderStructure_CoreAI>(TEXT("Rule_FolderStructure_CoreAI")));
	Rules.Add(CreateDefaultSubobject<UEarendilConventionRule_AssetNaming_CharacterAnimations>(TEXT("Rule_AssetNaming_CharacterAnimations")));
	Rules.Add(CreateDefaultSubobject<UEarendilConventionRule_AssetNaming_StateTree>(TEXT("Rule_AssetNaming_StateTree")));
}
