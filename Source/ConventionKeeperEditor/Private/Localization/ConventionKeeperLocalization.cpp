// Pavel Penkov 2025 All Rights Reserved.
// Shared validation messages only. Rule descriptions live in each Convention (e.g. UHLConventionStrings_*.inl).
// To add a language: add Strings_xx.inl in this folder and a branch in GetStringsForLanguage().

#include "Localization/ConventionKeeperLocalization.h"
#include "Development/ConventionKeeperSettings.h"

namespace
{
	static const TMap<FName, FString> GConventionKeeperStrings_en = {
#include "Strings_en.inl"
	};

	static const TMap<FName, FString> GConventionKeeperStrings_ru = {
#include "Strings_ru.inl"
	};

	const TMap<FName, FString>* GetStringsForLanguage(const FString& LanguageCode)
	{
		if (LanguageCode.StartsWith(TEXT("ru"), ESearchCase::IgnoreCase))
		{
			return &GConventionKeeperStrings_ru;
		}
		return &GConventionKeeperStrings_en;
	}
}

namespace ConventionKeeperLoc
{
	FText GetText(FName Key)
	{
		const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
		const FString Lang = Settings ? Settings->GetEffectiveLanguageCode() : TEXT("en");
		return GetTextForLanguage(Key, Lang);
	}

	FText GetTextForLanguage(FName Key, const FString& LanguageCode)
	{
		const TMap<FName, FString>* Map = GetStringsForLanguage(LanguageCode);
		const FString* Str = Map->Find(Key);
		if (!Str)
		{
			return FText::FromName(Key);
		}
		return FText::FromString(*Str);
	}
}
