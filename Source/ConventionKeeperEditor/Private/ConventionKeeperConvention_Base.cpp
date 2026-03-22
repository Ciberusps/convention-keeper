// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperConvention_Base.h"
#include "ConventionKeeperBlueprintLibrary.h"
#include "ConventionKeeperValidationHooks.h"
#include "Development/ConventionKeeperSettings.h"
#include "Rules/ConventionKeeperRule.h"
#include "Localization/ConventionKeeperLocalization.h"
#include "Logging/MessageLog.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "UObject/UnrealType.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperConvention_Base)

namespace
{
FString ConventionKeeperSlugifyConventionName(const FString& InName)
{
	FString S = InName.TrimStartAndEnd().ToLower();
	S.ReplaceInline(TEXT("_"), TEXT("-"));
	S.ReplaceInline(TEXT(" "), TEXT("-"));
	FString Out;
	for (const TCHAR* P = *S; *P; ++P)
	{
		const TCHAR C = *P;
		const bool bSlugChar =
			(C >= TEXT('a') && C <= TEXT('z')) || (C >= TEXT('0') && C <= TEXT('9')) || C == TEXT('-');
		if (bSlugChar)
		{
			Out.AppendChar(C);
		}
	}
	while (Out.ReplaceInline(TEXT("--"), TEXT("-")))
	{
	}
	Out.TrimStartAndEndInline();
	while (Out.Len() > 0 && Out[0] == TEXT('-'))
	{
		Out.RightChopInline(1);
	}
	while (Out.Len() > 0 && Out[Out.Len() - 1] == TEXT('-'))
	{
		Out.LeftChopInline(1);
	}
	return Out;
}
}

namespace ConventionKeeperConventionDocPaths
{
static bool ResolveDocPathToAbsolute(const FString& RelPath, FString& OutAbsolutePath)
{
	OutAbsolutePath = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectDir(), RelPath));
	if (FPaths::FileExists(OutAbsolutePath))
	{
		return true;
	}
	for (const FString& PluginName : { TEXT("ConventionKeeper"), TEXT("convention-keeper") })
	{
		if (TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(PluginName))
		{
			const FString PluginPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(Plugin->GetBaseDir(), RelPath));
			if (FPaths::FileExists(PluginPath))
			{
				OutAbsolutePath = PluginPath;
				return true;
			}
		}
	}
	return false;
}
}

FString UConventionKeeperConvention_Base::GetConventionDocumentationSlugForUrls() const
{
	if (!DocsIdOverride.IsNone())
	{
		const FString Id = DocsIdOverride.ToString();
		if (!Id.IsEmpty())
		{
			return Id;
		}
	}
	return ConventionKeeperSlugifyConventionName(Name);
}

FString UConventionKeeperConvention_Base::GetConventionDocumentationUrl() const
{
	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	const FString DocId = GetConventionDocumentationSlugForUrls();
	if (!Settings || Settings->DocsRepositoryUrl.IsEmpty() || DocId.IsEmpty())
	{
		return FString();
	}
	FString Path = DocsPathOverride;
	if (Path.IsEmpty())
	{
		Path = Settings->DocsConventionPathTemplate;
		Path.ReplaceInline(TEXT("{ConventionDocId}"), *DocId);
	}
	FString Base = Settings->DocsRepositoryUrl;
	while (Base.EndsWith(TEXT("/")))
	{
		Base.LeftChopInline(1);
	}
	const FString Branch = Settings->DocsBranch.IsEmpty() ? TEXT("main") : Settings->DocsBranch;
	return FString::Printf(TEXT("%s/blob/%s/%s"), *Base, *Branch, *Path);
}

FString UConventionKeeperConvention_Base::GetConventionDocumentationUrlForDisplay() const
{
	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	const FString DocId = GetConventionDocumentationSlugForUrls();
	if (!Settings || Settings->DocsRepositoryUrl.IsEmpty() || DocId.IsEmpty())
	{
		return GetConventionDocumentationUrl();
	}
	FString RelPathBase = DocsPathOverride.IsEmpty()
		? Settings->DocsConventionPathTemplate.Replace(TEXT("{ConventionDocId}"), *DocId)
		: DocsPathOverride;
	const FString Dir = FPaths::GetPath(RelPathBase);
	const FString BaseName = FPaths::GetBaseFilename(RelPathBase, true);
	const FString Ext = FPaths::GetExtension(RelPathBase, true);
	const FString Lang = Settings->GetEffectiveLanguageCode();
	TArray<FString> PathsToTry;
	if (!Lang.IsEmpty() && Lang != TEXT("en"))
	{
		PathsToTry.Add(FPaths::Combine(Dir, Lang, BaseName + Ext));
	}
	PathsToTry.Add(RelPathBase);
	FString LocalPath;
	FString ResolvedRelPath;
	for (const FString& RelPath : PathsToTry)
	{
		if (ConventionKeeperConventionDocPaths::ResolveDocPathToAbsolute(RelPath, LocalPath))
		{
			ResolvedRelPath = RelPath;
			break;
		}
	}
	if (ResolvedRelPath.IsEmpty())
	{
		return GetConventionDocumentationUrl();
	}
	FString Base = Settings->DocsRepositoryUrl;
	while (Base.EndsWith(TEXT("/")))
	{
		Base.LeftChopInline(1);
	}
	const FString Branch = Settings->DocsBranch.IsEmpty() ? TEXT("main") : Settings->DocsBranch;
	return FString::Printf(TEXT("%s/blob/%s/%s"), *Base, *Branch, *ResolvedRelPath);
}

void UConventionKeeperConvention_Base::RefreshConventionDocumentationFields()
{
#if WITH_EDITOR
	DocsUrl = GetConventionDocumentationUrl();
#endif
}

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

void UConventionKeeperConvention_Base::RebuildExtendedRules()
{
	SyncExtendsConventionAssetFlag();
	RefreshExtendedRules();
#if WITH_EDITOR
	for (UConventionKeeperRule* Rule : ExtendedRules)
	{
		if (Rule)
		{
			Rule->RefreshDocumentationFields();
		}
	}
	RefreshConventionDocumentationFields();
#endif
}

void UConventionKeeperConvention_Base::PostLoad()
{
	Super::PostLoad();
	RebuildExtendedRules();
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
#if WITH_EDITOR
		ApplyInheritedConventionDefaultsIfNeeded();
#endif
		RebuildExtendedRules();
	}
#if WITH_EDITOR
	else
	{
		RefreshConventionDocumentationFields();
	}
#endif
}

#if WITH_EDITOR
void UConventionKeeperConvention_Base::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
	RefreshConventionDocumentationFields();
}
#endif

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

void UConventionKeeperConvention_Base::SetExtendsConventionClass(TSubclassOf<UConventionKeeperConvention_Base> InExtendsConvention)
{
	ExtendsConvention = InExtendsConvention;
#if WITH_EDITOR
	ApplyInheritedConventionDefaultsIfNeeded();
#endif
	RebuildExtendedRules();
}

#if WITH_EDITOR
void UConventionKeeperConvention_Base::ApplyInheritedConventionDefaultsIfNeeded()
{
	const UConventionKeeperConvention_Base* Base = GetResolvedExtendsConvention();
	if (!Base)
	{
		return;
	}
	FString ParentLabel = Base->Name;
	if (ParentLabel.IsEmpty())
	{
		ParentLabel = Base->GetClass()->GetName();
		ParentLabel.RemoveFromEnd(TEXT("_C"));
	}
	if (Name.IsEmpty())
	{
		Name = ParentLabel;
	}
	if (Description.IsEmpty())
	{
		Description = FText::Format(
			NSLOCTEXT("ConventionKeeper", "ConventionInheritsDescription", "This convention extends \"{0}\"."),
			FText::FromString(ParentLabel));
	}
}
#endif

TArray<UConventionKeeperRule*> UConventionKeeperConvention_Base::GetEffectiveRules() const
{
	UConventionKeeperConvention_Base const* Base = GetResolvedExtendsConvention();
	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	const bool bDebug = Settings && Settings->bDebug;

	auto AddRuleIfAvailable = [bDebug](TArray<UConventionKeeperRule*>& Out, UConventionKeeperRule* Rule)
	{
		if (!Rule)
		{
			return;
		}
		FString Reason;
		if (!Rule->AreRequirementsSatisfied(&Reason))
		{
			if (bDebug)
			{
				const FString RuleName = Rule->RuleId.IsNone() ? Rule->GetClass()->GetName() : Rule->RuleId.ToString();
				UE_LOG(LogTemp, Log, TEXT("[ConventionKeeper] Rule skipped: %s (%s)"), *RuleName, *Reason);
			}
			return;
		}
		Out.Add(Rule);
	};

	if (!Base)
	{
		TArray<UConventionKeeperRule*> Out;
		for (UConventionKeeperRule* Rule : Rules)
		{
			AddRuleIfAvailable(Out, Rule);
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
			AddRuleIfAvailable(Out, Rule);
			continue;
		}
		if (const FRuleOverride* Override = OverrideMap.Find(Rule->RuleId))
		{
			switch (Override->Mode)
			{
			case EConventionRuleOverrideMode::Off:
				break;
			case EConventionRuleOverrideMode::Replace:
				AddRuleIfAvailable(Out, Override->ReplacementRule);
				break;
			default:
				AddRuleIfAvailable(Out, Rule);
				break;
			}
		}
		else
		{
			AddRuleIfAvailable(Out, Rule);
		}
	}

	for (UConventionKeeperRule* Rule : Rules)
	{
		AddRuleIfAvailable(Out, Rule);
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
	ValidateFolderStructuresForPathsInternal(TArray<FString>(), nullptr);
}

void UConventionKeeperConvention_Base::ValidateFolderStructuresForPaths(const TArray<FString>& SelectedPaths)
{
	ValidateFolderStructuresForPathsInternal(SelectedPaths, nullptr);
}

void UConventionKeeperConvention_Base::ValidateFolderStructuresForPathsInternal(
	const TArray<FString>& SelectedPaths,
	const FConventionKeeperValidationHooks* Hooks)
{
	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	const TMap<FString, FString> Placeholders = Settings ? Settings->GetPlaceholders() : TMap<FString, FString>();

	if (!IsRunningCommandlet())
	{
		FMessageLog(TEXT("ConventionKeeper")).NewPage(ConventionKeeperLoc::GetText(FName(TEXT("ConventionValidationPage"))));
	}

	const TArray<UConventionKeeperRule*> EffectiveRules = GetEffectiveRules();
	for (int32 RuleIndex = 0; RuleIndex < EffectiveRules.Num(); ++RuleIndex)
	{
		UConventionKeeperRule* Rule = EffectiveRules[RuleIndex];
		if (Hooks && Hooks->OnRuleProgress)
		{
			Hooks->OnRuleProgress(RuleIndex, EffectiveRules.Num(), Rule);
		}
		if (Hooks && Hooks->ShouldAbort && Hooks->ShouldAbort())
		{
			break;
		}
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
