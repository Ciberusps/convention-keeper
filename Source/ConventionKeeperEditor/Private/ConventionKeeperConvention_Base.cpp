// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperConvention_Base.h"
#include "ConventionKeeperBlueprintLibrary.h"
#include "Development/ConventionKeeperSettings.h"
#include "Rules/ConventionKeeperRule.h"
#include "Localization/ConventionKeeperLocalization.h"
#include "Logging/MessageLog.h"
#include "Misc/Paths.h"
#include "UObject/UnrealType.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperConvention_Base)

FText UConventionKeeperConvention_Base::GetLocalizedRuleDescription(FName RuleId) const
{
	return FText();
}

void UConventionKeeperConvention_Base::SyncExtendsConventionAssetFlag()
{
	bExtendsConventionAssetIsSet = !ExtendsConventionAsset.IsNull();
}

void UConventionKeeperConvention_Base::RefreshExtendedRules()
{
	ExtendedRules.Empty();
	UConventionKeeperConvention_Base const* Base = GetResolvedExtendsConvention();
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

void UConventionKeeperConvention_Base::PostLoad()
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
	for (UConventionKeeperRule* Rule : ExtendedRules)
	{
		if (Rule)
		{
			Rule->RefreshDocumentationFields();
		}
	}
#endif
}

void UConventionKeeperConvention_Base::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	const FName PropName = PropertyChangedEvent.GetPropertyName();
	if (PropName == GET_MEMBER_NAME_CHECKED(UConventionKeeperConvention_Base, ExtendsConventionAsset))
	{
		SyncExtendsConventionAssetFlag();
	}
	if (PropName == GET_MEMBER_NAME_CHECKED(UConventionKeeperConvention_Base, ExtendsConvention)
		|| PropName == GET_MEMBER_NAME_CHECKED(UConventionKeeperConvention_Base, ExtendsConventionAsset))
	{
		RefreshExtendedRules();
#if WITH_EDITOR
		for (UConventionKeeperRule* Rule : ExtendedRules)
		{
			if (Rule)
			{
				Rule->RefreshDocumentationFields();
			}
		}
#endif
	}
}

UConventionKeeperConvention_Base const* UConventionKeeperConvention_Base::GetResolvedExtendsConvention() const
{
	if (ExtendsConventionAsset.IsValid())
	{
		UConventionKeeperConvention_Base const* Asset = ExtendsConventionAsset.Get();
		return (Asset && Asset != this) ? Asset : nullptr;
	}
	if (ExtendsConvention.Get())
	{
		UConventionKeeperConvention_Base const* BaseCDO = ExtendsConvention->GetDefaultObject<UConventionKeeperConvention_Base>();
		return (BaseCDO && BaseCDO != this) ? BaseCDO : nullptr;
	}
	return nullptr;
}

TArray<FString> UConventionKeeperConvention_Base::GetAvailableRuleIds() const
{
	TArray<FString> Out;
	UConventionKeeperConvention_Base const* Base = GetResolvedExtendsConvention();
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

TArray<UConventionKeeperRule*> UConventionKeeperConvention_Base::GetEffectiveRules() const
{
	UConventionKeeperConvention_Base const* Base = GetResolvedExtendsConvention();

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

TSet<FString> UConventionKeeperConvention_Base::ExtractTemplatesFromPath(
	const FString& Path,
	const TMap<FString, FString>& GlobalPlaceholders)
{
	return UConventionKeeperBlueprintLibrary::ExtractTemplatesFromPath(Path, GlobalPlaceholders);
}

void UConventionKeeperConvention_Base::ValidateFolderStructures_Implementation()
{
	ValidateFolderStructuresForPaths(TArray<FString>());
}

void UConventionKeeperConvention_Base::ValidateFolderStructuresForPaths(const TArray<FString>& SelectedPaths)
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
		FMessageLog Log(TEXT("ConventionKeeper"));
		if (Log.NumMessages(EMessageSeverity::Info) > 0)
		{
			Log.Open(EMessageSeverity::Info, true);
		}
	}
}

bool UConventionKeeperConvention_Base::DoesDirectoryExist(const FString& DirectoryPath, const TMap<FString, FString>& Placeholders)
{
	FString Resolved = DirectoryPath;
	for (const TTuple<FString, FString>& Pair : Placeholders)
	{
		Resolved = Resolved.Replace(*Pair.Key, *Pair.Value, ESearchCase::CaseSensitive);
	}
	const FString Absolute = FPaths::ProjectDir() / Resolved;
	return FPaths::DirectoryExists(Absolute);
}
