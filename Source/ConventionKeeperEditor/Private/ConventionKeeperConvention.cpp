// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperConvention.h"
#include "Development/ConventionKeeperSettings.h"
#include "HAL/FileManager.h"
#include "Logging/MessageLog.h"
#include "Misc/Paths.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperConvention)

TArray<UConventionKeeperRule*> UConventionKeeperConvention::GetEffectiveRules() const
{
	UConventionKeeperConvention const* Base = nullptr;
	if (ExtendsConvention.Get())
	{
		UConventionKeeperConvention const* BaseCDO = ExtendsConvention->GetDefaultObject<UConventionKeeperConvention>();
		if (BaseCDO == this)
		{
			Base = nullptr;
		}
		else
		{
			Base = BaseCDO;
		}
	}

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

	for (UConventionKeeperRule* Rule : AdditionalRules)
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
	TSet<FString> Result;
	FString Remainder = Path;
	while (true)
	{
		const int32 Open = Remainder.Find(TEXT("{"), ESearchCase::CaseSensitive);
		if (Open == INDEX_NONE)
		{
			break;
		}
		const int32 Close = Remainder.Find(TEXT("}"), ESearchCase::CaseSensitive, ESearchDir::FromStart, Open);
		if (Close == INDEX_NONE)
		{
			break;
		}
		FString Segment = Remainder.Mid(Open + 1, Close - Open - 1).TrimStartAndEnd();
		Remainder = Remainder.Mid(Close + 1);
		if (Segment.Len() >= 1)
		{
			FString Key = FString::Printf(TEXT("{%s}"), *Segment);
			if (!GlobalPlaceholders.Contains(Key))
			{
				Result.Add(Segment);
			}
		}
	}
	return Result;
}

static void ResolveTemplatePathsRecurse(
	const FString& Prefix,
	const FString& PatternTail,
	const TMap<FString, FString>& GlobalPlaceholders,
	TArray<FString>& OutPaths)
{
	FString Normalized = PatternTail;
	Normalized.ReplaceInline(TEXT("\\"), TEXT("/"));
	Normalized.TrimStartAndEndInline();
	if (Normalized.IsEmpty())
	{
		OutPaths.Add(Prefix);
		return;
	}

	FString Segment;
	FString Rest;
	if (!Normalized.Split(TEXT("/"), &Segment, &Rest))
	{
		Segment = Normalized;
		Rest = FString();
	}

	if (Segment.StartsWith(TEXT("{")) && Segment.EndsWith(TEXT("}")))
	{
		FString PlaceholderKey = Segment;
		FString TemplateName = Segment.Mid(1, Segment.Len() - 2);
		if (GlobalPlaceholders.Contains(PlaceholderKey))
		{
			FString Literal = GlobalPlaceholders[PlaceholderKey];
			FString NewPrefix = Prefix.IsEmpty() ? Literal : (Prefix / Literal);
			ResolveTemplatePathsRecurse(NewPrefix, Rest, GlobalPlaceholders, OutPaths);
			return;
		}
		FString BasePath = FPaths::IsRelative(Prefix) ? (FPaths::ProjectDir() / Prefix) : Prefix;
		BasePath.ReplaceInline(TEXT("\\"), TEXT("/"));
		if (!BasePath.EndsWith(TEXT("/")))
		{
			BasePath += TEXT("/");
		}
		TArray<FString> SubDirs;
		IFileManager::Get().FindFiles(SubDirs, *BasePath, false, true);
		for (const FString& Sub : SubDirs)
		{
			FString NewPrefix = Prefix.IsEmpty() ? Sub : (Prefix / Sub);
			ResolveTemplatePathsRecurse(NewPrefix, Rest, GlobalPlaceholders, OutPaths);
		}
		return;
	}

	FString NewPrefix = Prefix.IsEmpty() ? Segment : (Prefix / Segment);
	ResolveTemplatePathsRecurse(NewPrefix, Rest, GlobalPlaceholders, OutPaths);
}

TArray<FString> UConventionKeeperConvention::ResolveTemplatePaths(
	const FString& FullPattern,
	const TMap<FString, FString>& GlobalPlaceholders)
{
	TArray<FString> Out;
	FString Normalized = FullPattern;
	Normalized.ReplaceInline(TEXT("\\"), TEXT("/"));
	Normalized.TrimStartAndEndInline();
	while (Normalized.StartsWith(TEXT("/")))
	{
		Normalized.RemoveFromStart(TEXT("/"));
	}
	ResolveTemplatePathsRecurse(FString(), Normalized, GlobalPlaceholders, Out);
	for (FString& Path : Out)
	{
		Path = FString(TEXT("/")) + Path;
	}
	return Out;
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
		FMessageLog(TEXT("ConventionKeeper")).NewPage(FText::FromString(TEXT("Convention validation")));
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
