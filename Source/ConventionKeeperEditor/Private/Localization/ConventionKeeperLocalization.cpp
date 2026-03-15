// Pavel Penkov 2025 All Rights Reserved.

#include "Localization/ConventionKeeperLocalization.h"
#include "Development/ConventionKeeperSettings.h"

#define CONVENTION_KEEPER_LOC_KEY(Key, En, Ru) { FName(TEXT(Key)), { TEXT(En), TEXT(Ru) } }

namespace
{
	const TMap<FName, TTuple<FString, FString>>& GetStringTable()
	{
		static const TMap<FName, TTuple<FString, FString>> Table = {
			CONVENTION_KEEPER_LOC_KEY("Desc_folder_content",
				"Root Content folder must contain 3rdParty, {ProjectName}, FMOD, Movies.",
				"В корне Content должны быть папки: 3rdParty, {ProjectName}, FMOD, Movies."),
			CONVENTION_KEEPER_LOC_KEY("Desc_folder_project_name",
				"Under Content/{ProjectName}/ require Characters, Maps, Core, SFX, VFX, AI.",
				"В Content/{ProjectName}/ обязательны папки: Characters, Maps, Core, SFX, VFX, AI."),
			CONVENTION_KEEPER_LOC_KEY("Desc_folder_character",
				"Each character folder must have AI, Projectiles, Animations, Gyms, Data, Abilities, Materials.",
				"В каждой папке персонажа должны быть: AI, Projectiles, Animations, Gyms, Data, Abilities, Materials."),
			CONVENTION_KEEPER_LOC_KEY("Desc_folder_core_ai",
				"Content/{ProjectName}/Core/AI/ must exist.",
				"Папка Content/{ProjectName}/Core/AI/ должна существовать."),
			CONVENTION_KEEPER_LOC_KEY("Desc_asset_naming_character_animations",
				"Animations in Content/{ProjectName}/Characters/{CharacterName}/Animations must be named AS_{CharacterName}_* with optional zero-padded number suffix (e.g. AS_Zombie_Jump_01).",
				"Анимации в Content/{ProjectName}/Characters/{CharacterName}/Animations должны называться AS_{CharacterName}_* с опциональным нулевым суффиксом (напр. AS_Zombie_Jump_01)."),

			CONVENTION_KEEPER_LOC_KEY("FolderMissing", "[{0}] Required folder is missing: ", "[{0}] Требуемая папка отсутствует: "),
			CONVENTION_KEEPER_LOC_KEY("FolderExists", "[{0}] Folder exists: ", "[{0}] Папка найдена: "),
			CONVENTION_KEEPER_LOC_KEY("RequiredSubfolderMissing", "[{0}] Required folder is missing: ", "[{0}] Требуемая папка отсутствует: "),
			CONVENTION_KEEPER_LOC_KEY("RequiredSubfolderMissingSuffix", " (under {0})", " (в {0})"),
			CONVENTION_KEEPER_LOC_KEY("RequiredSubfolderExists", "[{0}] Required folder exists: ", "[{0}] Требуемая папка найдена: "),
			CONVENTION_KEEPER_LOC_KEY("DisallowedFolder", "[{0}] Folder not allowed in ", "[{0}] Папка не допускается в "),
			CONVENTION_KEEPER_LOC_KEY("DisallowedFolderSuffix", ": {0}", ": {0}"),
			CONVENTION_KEEPER_LOC_KEY("NoExtraFolders", "[{0}] No disallowed folders in ", "[{0}] Нет лишних папок в "),
			CONVENTION_KEEPER_LOC_KEY("FolderOkSuffix", " — OK", " — OK"),

			CONVENTION_KEEPER_LOC_KEY("AssetNamingPrefix", "[{0}] Asset must start with prefix: ", "[{0}] Имя ассета должно начинаться с префикса: "),
			CONVENTION_KEEPER_LOC_KEY("AssetNamingPrefixSuffix", " (expected \"{0}\")", " (ожидается \"{0}\")"),
			CONVENTION_KEEPER_LOC_KEY("AssetNamingSuffix", "[{0}] Asset must end with suffix: ", "[{0}] Имя ассета должно заканчиваться суффиксом: "),
			CONVENTION_KEEPER_LOC_KEY("AssetNamingSuffixVal", " (expected \"{0}\")", " (ожидается \"{0}\")"),
			CONVENTION_KEEPER_LOC_KEY("AssetNamingNumber", "[{0}] Numeric suffix must be zero-padded to {1} digits: ", "[{0}] Числовой суффикс должен иметь {1} цифр с нулём: "),
			CONVENTION_KEEPER_LOC_KEY("AssetNamingSuggest", " (e.g. use \"{0}\")", " (напр. используйте \"{0}\")"),
			CONVENTION_KEEPER_LOC_KEY("AssetNamingOk", "[{0}] Asset name OK: ", "[{0}] Имя ассета OK: "),

			CONVENTION_KEEPER_LOC_KEY("ConventionValidationPage", "Convention validation", "Проверка конвенции"),
		};
		return Table;
	}
}

#undef CONVENTION_KEEPER_LOC_KEY

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
		const TMap<FName, TTuple<FString, FString>>& Table = GetStringTable();
		const TTuple<FString, FString>* Pair = Table.Find(Key);
		if (!Pair)
		{
			return FText::FromName(Key);
		}
		const bool bRussian = LanguageCode.StartsWith(TEXT("ru"), ESearchCase::IgnoreCase);
		const FString& Str = bRussian ? Pair->Get<1>() : Pair->Get<0>();
		return FText::FromString(Str);
	}
}
