// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperConvention.h"
#include "ConventionKeeperBlueprintLibrary.h"
#include "Development/ConventionKeeperSettings.h"
#include "Rules/ConventionKeeperRule.h"
#include "Localization/ConventionKeeperLocalization.h"
#include "Logging/MessageLog.h"
#include "Misc/Paths.h"
#include "UObject/UnrealType.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperConvention)

FText UConventionKeeperConvention::GetLocalizedRuleDescription(FName RuleId) const
{
	return FText();
}

void UConventionKeeperConvention::SyncExtendsConventionAssetFlag()
{
	bExtendsConventionAssetIsSet = !ExtendsConventionAsset.IsNull();
}

void UConventionKeeperConvention::RefreshExtendedRules()
{
	ExtendedRules.Empty();
	UConventionKeeperConvention const* Base = GetResolvedExtendsConvention();
	if (Base)
	{
		for (UConventionKeeperRule* Rule : Base->GetEffectiveRules())
		{
			if (Rule)
			{
				ExtendedRules.Add(Rule);
			}
		}
	}
}

void UConventionKeeperConvention::PostLoad()
{
	Super::PostLoad();
	SyncExtendsConventionAssetFlag();
	RefreshExtendedRules();
#if WITH_EDITOR
	for (UConventionKeeperRule* Rule : Rules)
	{
		if (Rule)
		{
			Rule->RefreshDocumentationFields();
		}
	}
#endif
}

void UConventionKeeperConvention::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	const FName PropName = PropertyChangedEvent.GetPropertyName();
	if (PropName == GET_MEMBER_NAME_CHECKED(UConventionKeeperConvention, ExtendsConventionAsset))
	{
		SyncExtendsConventionAssetFlag();
	}
	if (PropName == GET_MEMBER_NAME_CHECKED(UConventionKeeperConvention, ExtendsConvention)
		|| PropName == GET_MEMBER_NAME_CHECKED(UConventionKeeperConvention, ExtendsConventionAsset))
	{
		RefreshExtendedRules();
	}
}

UConventionKeeperConvention const* UConventionKeeperConvention::GetResolvedExtendsConvention() const
{
	if (ExtendsConventionAsset.IsValid())
	{
		UConventionKeeperConvention const* Asset = ExtendsConventionAsset.Get();
		return (Asset && Asset != this) ? Asset : nullptr;
	}
	if (ExtendsConvention.Get())
	{
		UConventionKeeperConvention const* BaseCDO = ExtendsConvention->GetDefaultObject<UConventionKeeperConvention>();
		return (BaseCDO && BaseCDO != this) ? BaseCDO : nullptr;
	}
	return nullptr;
}

TArray<FString> UConventionKeeperConvention::GetAvailableRuleIds() const
{
	TArray<FString> Out;
	UConventionKeeperConvention const* Base = GetResolvedExtendsConvention();
	if (!Base)
	{
		return Out;
	}
	for (UConventionKeeperRule* Rule : Base->GetEffectiveRules())
	{
		if (Rule && !Rule->RuleId.IsNone())
		{
			Out.AddUnique(Rule->RuleId.ToString());
		}
	}
	return Out;
}

TArray<UConventionKeeperRule*> UConventionKeeperConvention::GetEffectiveRules() const
{
	UConventionKeeperConvention const* Base = GetResolvedExtendsConvention();

	if (!Base)
	{
		TArray<UConventionKeeperRule*> Out;
		for (UConventionKeeperRule* Rule : Rules)
		{
			if (Rule)
			{
				Out.Add(Rule);
			}
		}
		return Out;
	}

	TMap<FName, FRuleOverride> OverrideMap;
	for (const FRuleOverride& Override : RuleOverrides)
	{
		if (Override.RuleId.IsNone())
		{
			continue;
		}
		OverrideMap.FindOrAdd(Override.RuleId) = Override;
	}

	TArray<UConventionKeeperRule*> Out;
	for (UConventionKeeperRule* Rule : Base->GetEffectiveRules())
	{
		if (!Rule)
		{
			continue;
		}
		if (Rule->RuleId.IsNone())
		{
			Out.Add(Rule);
			continue;
		}
		if (const FRuleOverride* Override = OverrideMap.Find(Rule->RuleId))
		{
			switch (Override->Mode)
			{
			case EConventionRuleOverrideMode::Off:
				break;
			case EConventionRuleOverrideMode::Replace:
				if (Override->ReplacementRule)
				{
					Out.Add(Override->ReplacementRule);
				}
				break;
			default:
				Out.Add(Rule);
				break;
			}
		}
		else
		{
			Out.Add(Rule);
		}
	}

	for (UConventionKeeperRule* Rule : Rules)
	{
		if (Rule)
		{
			Out.Add(Rule);
		}
	}

	return Out;
}

TSet<FString> UConventionKeeperConvention::ExtractTemplatesFromPath(
	const FString& Path,
	const TMap<FString, FString>& GlobalPlaceholders)
{
	return UConventionKeeperBlueprintLibrary::ExtractTemplatesFromPath(Path, GlobalPlaceholders);
}

void UConventionKeeperConvention::ValidateFolderStructures_Implementation()
{
	ValidateFolderStructuresForPaths(TArray<FString>());
}

void UConventionKeeperConvention::ValidateFolderStructuresForPaths(const TArray<FString>& SelectedPaths)
{
	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	const TMap<FString, FString> Placeholders = Settings ? Settings->GetPlaceholders() : TMap<FString, FString>();

	if (!IsRunningCommandlet())
	{
		FMessageLog(TEXT("ConventionKeeper")).NewPage(ConventionKeeperLoc::GetText(FName(TEXT("ConventionValidationPage"))));
	}

	const TArray<UConventionKeeperRule*> EffectiveRules = GetEffectiveRules();
	for (UConventionKeeperRule* Rule : EffectiveRules)
	{
		if (Rule && Rule->CanValidate(SelectedPaths, Placeholders))
		{
			Rule->Validate(SelectedPaths, Placeholders);
		}
	}

	if (!IsRunningCommandlet())
	{
		FMessageLog(TEXT("ConventionKeeper")).Open(EMessageSeverity::Info, true);
	}
}

bool UConventionKeeperConvention::DoesDirectoryExist(const FString& DirectoryPath, const TMap<FString, FString>& Placeholders)
{
	FString Resolved = DirectoryPath;
	for (const TTuple<FString, FString>& Pair : Placeholders)
	{
		Resolved = Resolved.Replace(*Pair.Key, *Pair.Value, ESearchCase::CaseSensitive);
	}
	const FString Absolute = FPaths::ProjectDir() / Resolved;
	return FPaths::DirectoryExists(Absolute);
}
