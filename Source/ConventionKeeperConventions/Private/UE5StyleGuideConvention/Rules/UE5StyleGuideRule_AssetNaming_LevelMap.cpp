// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_LevelMap.h"
#include "Localization/ConventionKeeperLocalization.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_LevelMap)

static const TCHAR* LevelMapAllowedSuffixes[] = {
	TEXT("_P"),
	TEXT("_Audio"),
	TEXT("_Lighting"),
	TEXT("_Geo"),
	TEXT("_Gameplay"),
};

UUE5StyleGuideRule_AssetNaming_LevelMap::UUE5StyleGuideRule_AssetNaming_LevelMap()
{
	RuleId = FName(TEXT("asset-naming-level-map"));
	Description = FText::FromString(TEXT("Level/Map (World) assets may have no suffix or one of: _P (Persistent), _Audio, _Lighting, _Geo, _Gameplay (UE5 Style Guide 1.2.1)."));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-level-map"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}/Maps");
	AssetClassPaths.Add(TEXT("/Script/Engine.World"));
	Prefix = TEXT("");
}

bool UUE5StyleGuideRule_AssetNaming_LevelMap::GetCustomSuffixValidity(const FString& AssetName, const FString& UsedPrefix, bool& OutValid) const
{
	int32 Idx;
	if (!AssetName.FindLastChar(TEXT('_'), Idx) || Idx <= 0 || Idx == AssetName.Len() - 1)
	{
		OutValid = true;
		return true;
	}
	const FString LocalSuffix = AssetName.Mid(Idx);
	for (const TCHAR* Allowed : LevelMapAllowedSuffixes)
	{
		if (LocalSuffix.Equals(Allowed, ESearchCase::IgnoreCase))
		{
			OutValid = true;
			return true;
		}
	}
	OutValid = false;
	return true;
}

FText UUE5StyleGuideRule_AssetNaming_LevelMap::GetCustomSuffixFailureMessage(const FString& AssetName, const FString& UsedPrefix) const
{
	return ConventionKeeperLoc::GetText(FName(TEXT("RuleDesc_asset-naming-level-map")));
}
