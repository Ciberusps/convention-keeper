// Pavel Penkov 2025 All Rights Reserved.

#include "Rules/ConventionKeeperRule_AssetNaming.h"

#include "AssetRegistry/ARFilter.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "ConventionKeeperBlueprintLibrary.h"
#include "Development/ConventionKeeperSettings.h"
#include "Logging/MessageLog.h"
#include "Logging/TokenizedMessage.h"
#include "Misc/Paths.h"
#include "Misc/PackageName.h"

#define LOCTEXT_NAMESPACE "ConventionKeeperRule_AssetNaming"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperRule_AssetNaming)

FString UConventionKeeperRule_AssetNaming::NormalizeRelativePath(const FString& InPath)
{
	FString Result = InPath;
	Result.ReplaceInline(TEXT("\\"), TEXT("/"));
	if (!Result.EndsWith(TEXT("/")))
	{
		Result += TEXT("/");
	}
	return Result;
}

bool UConventionKeeperRule_AssetNaming::IsRelevantPath(const FString& ResolvedPath, const TArray<FString>& SelectedPaths)
{
	if (SelectedPaths.IsEmpty())
	{
		return true;
	}
	const FString NormalizedResolvedPath = NormalizeRelativePath(ResolvedPath);
	for (const FString& SelectedPath : SelectedPaths)
	{
		const FString NormalizedSelectedPath = NormalizeRelativePath(SelectedPath);
		if (NormalizedResolvedPath.StartsWith(NormalizedSelectedPath))
		{
			return true;
		}
	}
	return false;
}

bool UConventionKeeperRule_AssetNaming::IsPathUnderExcluded(const FString& ResolvedPath, const TArray<FString>& ExcludeFolders, const TMap<FString, FString>& Placeholders)
{
	const FString NormalizedPath = NormalizeRelativePath(ResolvedPath);
	for (const FString& ExcludeFolder : ExcludeFolders)
	{
		FString ResolvedExclude = ExcludeFolder;
		for (const TTuple<FString, FString>& Pair : Placeholders)
		{
			ResolvedExclude = ResolvedExclude.Replace(*Pair.Key, *Pair.Value, ESearchCase::CaseSensitive);
		}
		const FString NormalizedExclude = NormalizeRelativePath(ResolvedExclude);
		if (NormalizedPath.StartsWith(NormalizedExclude) || NormalizedExclude.StartsWith(NormalizedPath))
		{
			return true;
		}
	}
	return false;
}

bool UConventionKeeperRule_AssetNaming::ExtractPathPlaceholders(const FString& PatternPath, const FString& ResolvedPath, const TMap<FString, FString>& GlobalPlaceholders, TMap<FString, FString>& OutPathPlaceholders)
{
	return UConventionKeeperBlueprintLibrary::ExtractPathPlaceholders(PatternPath, ResolvedPath, GlobalPlaceholders, OutPathPlaceholders);
}

FString UConventionKeeperRule_AssetNaming::ResolveNamingTemplate(const FString& Template, const TMap<FString, FString>& PathPlaceholders)
{
	FString Result = Template;
	for (const TTuple<FString, FString>& Pair : PathPlaceholders)
	{
		Result = Result.Replace(*FString::Printf(TEXT("{%s}"), *Pair.Key), *Pair.Value, ESearchCase::CaseSensitive);
	}
	return Result;
}

bool UConventionKeeperRule_AssetNaming::IsNumberSuffixValid(const FString& AssetName, int32 PaddingDigits)
{
	if (PaddingDigits <= 0 || AssetName.IsEmpty())
	{
		return true;
	}
	int32 i = AssetName.Len() - 1;
	while (i >= 0 && FChar::IsDigit(AssetName[i]))
	{
		--i;
	}
	if (i < 0 || AssetName[i] != '_')
	{
		return true;
	}
	FString Suffix = AssetName.Mid(i + 1);
	return Suffix.Len() == PaddingDigits;
}

FString UConventionKeeperRule_AssetNaming::SuggestZeroPaddedName(const FString& AssetName, int32 PaddingDigits)
{
	if (PaddingDigits <= 0 || AssetName.IsEmpty())
	{
		return AssetName;
	}
	int32 i = AssetName.Len() - 1;
	while (i >= 0 && FChar::IsDigit(AssetName[i]))
	{
		--i;
	}
	if (i < 0 || AssetName[i] != '_')
	{
		return AssetName;
	}
	FString NumPart = AssetName.Mid(i + 1);
	int32 Val = 0;
	for (TCHAR c : NumPart)
	{
		Val = Val * 10 + (c - TEXT('0'));
	}
	FString Padded = FString::Printf(TEXT("%0*d"), PaddingDigits, Val);
	return AssetName.Left(i + 1) + Padded;
}

bool UConventionKeeperRule_AssetNaming::CanValidate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const
{
	FString ResolvedFolderPath = FolderPathPattern.Path;
	ResolvedFolderPath.ReplaceInline(TEXT("\\"), TEXT("/"));
	ResolvedFolderPath.TrimStartAndEndInline();
	if (ResolvedFolderPath.IsEmpty())
	{
		ResolvedFolderPath = TEXT("Content/{ProjectName}");
	}
	for (const TTuple<FString, FString>& Pair : Placeholders)
	{
		ResolvedFolderPath = ResolvedFolderPath.Replace(*Pair.Key, *Pair.Value, ESearchCase::CaseSensitive);
	}
	ResolvedFolderPath = NormalizeRelativePath(ResolvedFolderPath);

	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	if (Settings && IsPathUnderExcluded(ResolvedFolderPath, Settings->ExcludeFolders, Placeholders))
	{
		return false;
	}
	return IsRelevantPath(ResolvedFolderPath, SelectedPaths);
}

namespace AssetNamingRule
{
	static EMessageSeverity::Type RuleSeverityToMessageSeverity(EConventionRuleSeverity RuleSeverity)
	{
		return RuleSeverity == EConventionRuleSeverity::Warning ? EMessageSeverity::Warning : EMessageSeverity::Error;
	}

	static void LogRuleMessage(EMessageSeverity::Type Severity, const FText& Message, const FString* PathForLink = nullptr, const FText& Suffix = FText())
{
	if (IsRunningCommandlet())
	{
		FString Text = Message.ToString();
		if (PathForLink && !PathForLink->IsEmpty())
		{
			Text += *PathForLink;
		}
		if (!Suffix.IsEmpty())
		{
			Text += Suffix.ToString();
		}
		switch (Severity)
		{
		case EMessageSeverity::Error:
			UE_LOG(LogTemp, Error, TEXT("%s"), *Text);
			break;
		case EMessageSeverity::Warning:
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Text);
			break;
		default:
			UE_LOG(LogTemp, Log, TEXT("%s"), *Text);
			break;
		}
	}
	else
	{
		if (PathForLink && !PathForLink->IsEmpty())
		{
			FString AssetPath = PathForLink->Replace(TEXT("\\"), TEXT("/"));
			if (AssetPath.StartsWith(TEXT("Content/")))
			{
				AssetPath = FString(TEXT("/Game/")) + AssetPath.Mid(8);
			}
			else if (!AssetPath.StartsWith(TEXT("/")))
			{
				AssetPath = FString(TEXT("/Game/")) + AssetPath;
			}
			TSharedRef<FTokenizedMessage> TokenizedMessage = FTokenizedMessage::Create(Severity);
			TokenizedMessage->AddToken(FTextToken::Create(Message));
			TokenizedMessage->AddToken(FAssetNameToken::Create(AssetPath, FText::FromString(*PathForLink)));
			if (!Suffix.IsEmpty())
			{
				TokenizedMessage->AddToken(FTextToken::Create(Suffix));
			}
			FMessageLog(TEXT("ConventionKeeper")).AddMessage(TokenizedMessage);
		}
		else
		{
			TSharedRef<FTokenizedMessage> TokenizedMessage = FTokenizedMessage::Create(Severity);
			TokenizedMessage->AddToken(FTextToken::Create(Message));
			if (!Suffix.IsEmpty())
			{
				TokenizedMessage->AddToken(FTextToken::Create(Suffix));
			}
			FMessageLog(TEXT("ConventionKeeper")).AddMessage(TokenizedMessage);
		}
	}
}
}

void UConventionKeeperRule_AssetNaming::Validate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders)
{
	if (!CanValidate_Implementation(SelectedPaths, Placeholders))
	{
		return;
	}

	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	const bool bDebug = Settings && Settings->bDebug;
	const EMessageSeverity::Type FailureSeverity = AssetNamingRule::RuleSeverityToMessageSeverity(Severity);

	FString PatternPath = FolderPathPattern.Path;
	PatternPath.ReplaceInline(TEXT("\\"), TEXT("/"));
	while (PatternPath.StartsWith(TEXT("/")))
	{
		PatternPath.RemoveFromStart(TEXT("/"));
	}
	if (PatternPath.IsEmpty())
	{
		PatternPath = TEXT("Content/{ProjectName}");
	}
	TMap<FString, FString> PlaceholdersWithBraces;
	if (Settings)
	{
		TMap<FString, FString> FromSettings = Settings->GetPlaceholders();
		for (const TTuple<FString, FString>& Pair : FromSettings)
		{
			FString Key = Pair.Key;
			if (!Key.StartsWith(TEXT("{")))
			{
				Key = FString::Printf(TEXT("{%s}"), *Pair.Key);
			}
			PlaceholdersWithBraces.Add(Key, Pair.Value);
		}
	}
	for (const TTuple<FString, FString>& Pair : Placeholders)
	{
		FString Key = Pair.Key;
		if (!Key.StartsWith(TEXT("{")))
		{
			Key = FString::Printf(TEXT("{%s}"), *Pair.Key);
		}
		PlaceholdersWithBraces.Add(Key, Pair.Value);
	}
	TArray<FString> ResolvedPaths = UConventionKeeperBlueprintLibrary::ResolveTemplatePaths(PatternPath, PlaceholdersWithBraces);
	if (ResolvedPaths.Num() == 0)
	{
		TSet<FString> TemplateNames = UConventionKeeperBlueprintLibrary::ExtractTemplatesFromPath(PatternPath, PlaceholdersWithBraces);
		if (TemplateNames.Num() == 0)
		{
			FString SinglePath = PatternPath;
			for (const TTuple<FString, FString>& Pair : PlaceholdersWithBraces)
			{
				SinglePath = SinglePath.Replace(*Pair.Key, *Pair.Value, ESearchCase::CaseSensitive);
			}
			SinglePath.ReplaceInline(TEXT("\\"), TEXT("/"));
			SinglePath.TrimStartAndEndInline();
			while (SinglePath.StartsWith(TEXT("/")))
			{
				SinglePath.RemoveFromStart(TEXT("/"));
			}
			if (!SinglePath.IsEmpty())
			{
				if (!SinglePath.StartsWith(TEXT("Content/")))
				{
					SinglePath = FString(TEXT("Content/")) + SinglePath;
				}
				ResolvedPaths.Add(FString(TEXT("/")) + SinglePath);
			}
		}
	}

	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();

	for (const FString& ResolvedPathWithSlash : ResolvedPaths)
	{
		FString ResolvedPath = ResolvedPathWithSlash;
		ResolvedPath.ReplaceInline(TEXT("\\"), TEXT("/"));
		if (ResolvedPath.StartsWith(TEXT("/")))
		{
			ResolvedPath.RemoveFromStart(TEXT("/"));
		}
		if (!ResolvedPath.StartsWith(TEXT("Content/")))
		{
			ResolvedPath = FString(TEXT("Content/")) + ResolvedPath;
		}
		FString PackagePath = FString(TEXT("/Game/")) + ResolvedPath.Mid(8);
		PackagePath.ReplaceInline(TEXT("/"), TEXT("/"));
		if (PackagePath.EndsWith(TEXT("/")))
		{
			PackagePath.LeftChopInline(1);
		}

		TMap<FString, FString> PathPlaceholders;
		if (!ExtractPathPlaceholders(PatternPath, ResolvedPath, PlaceholdersWithBraces, PathPlaceholders))
		{
			continue;
		}

		FString RequiredPrefix = NamingTemplate.IsEmpty()
			? (Prefix.IsEmpty() ? FString() : ResolveNamingTemplate(Prefix, PathPlaceholders))
			: ResolveNamingTemplate(NamingTemplate, PathPlaceholders);
		if (RequiredPrefix.IsEmpty())
		{
			continue;
		}

		FARFilter Filter;
		Filter.PackagePaths.Add(FName(*PackagePath));
		Filter.bRecursivePaths = true;
		for (TSubclassOf<UObject> Class : AssetClasses)
		{
			if (Class.Get())
			{
				Filter.ClassPaths.Add(FTopLevelAssetPath(Class.Get()));
			}
		}
		if (Filter.ClassPaths.IsEmpty())
		{
			continue;
		}

		TArray<FAssetData> AssetDataList;
		AssetRegistry.GetAssets(Filter, AssetDataList);

		for (const FAssetData& AssetData : AssetDataList)
		{
			FString AssetName = AssetData.AssetName.ToString();
			FString PackageName = AssetData.PackageName.ToString();
			FString RelativePath = PackageName;
			if (RelativePath.StartsWith(TEXT("/Game/")))
			{
				RelativePath = FString(TEXT("Content/")) + RelativePath.Mid(6);
			}
			RelativePath.ReplaceInline(TEXT("/"), TEXT("/"));

			bool bPrefixOk = RequiredPrefix.IsEmpty() || AssetName.StartsWith(RequiredPrefix);
			bool bSuffixOk = Suffix.IsEmpty() || AssetName.EndsWith(Suffix);
			bool bNumberOk = IsNumberSuffixValid(AssetName, NumberPaddingDigits);

			if (!bPrefixOk)
			{
				AssetNamingRule::LogRuleMessage(FailureSeverity,
					FText::Format(LOCTEXT("AssetNamingPrefix", "[{0}] Asset must start with prefix: "),
						FText::FromName(RuleId)),
					&RelativePath, FText::Format(LOCTEXT("AssetNamingPrefixSuffix", " (expected \"{0}\")"), FText::FromString(RequiredPrefix)));
			}
			else if (!bSuffixOk)
			{
				AssetNamingRule::LogRuleMessage(FailureSeverity,
					FText::Format(LOCTEXT("AssetNamingSuffix", "[{0}] Asset must end with suffix: "),
						FText::FromName(RuleId)),
					&RelativePath, FText::Format(LOCTEXT("AssetNamingSuffixVal", " (expected \"{0}\")"), FText::FromString(Suffix)));
			}
			else if (!bNumberOk)
			{
				FString Suggested = SuggestZeroPaddedName(AssetName, NumberPaddingDigits);
				AssetNamingRule::LogRuleMessage(FailureSeverity,
					FText::Format(LOCTEXT("AssetNamingNumber", "[{0}] Numeric suffix must be zero-padded to {1} digits: "),
						FText::FromName(RuleId), FText::AsNumber(NumberPaddingDigits)),
					&RelativePath, FText::Format(LOCTEXT("AssetNamingSuggest", " (e.g. use \"{0}\")"), FText::FromString(Suggested)));
			}
			else if (bDebug)
			{
				AssetNamingRule::LogRuleMessage(EMessageSeverity::Info,
					FText::Format(LOCTEXT("AssetNamingOk", "[{0}] Asset name OK: "), FText::FromName(RuleId)),
					&RelativePath, FText::FromString(TEXT("")));
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE

#if WITH_EDITOR
void UConventionKeeperRule_AssetNaming::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
