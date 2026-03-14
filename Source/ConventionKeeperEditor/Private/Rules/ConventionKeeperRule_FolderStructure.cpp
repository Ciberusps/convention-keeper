// Pavel Penkov 2025 All Rights Reserved.

#include "Rules/ConventionKeeperRule_FolderStructure.h"

#include "ConventionKeeperBlueprintLibrary.h"
#include "ConventionKeeperConvention.h"
#include "Development/ConventionKeeperSettings.h"
#include "Logging/MessageLog.h"
#include "Logging/TokenizedMessage.h"
#include "Misc/Paths.h"

#define LOCTEXT_NAMESPACE "ConventionKeeperRule_FolderStructure"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperRule_FolderStructure)

FString UConventionKeeperRule_FolderStructure::ResolvePlaceholdersForPath(const FString& DirectoryPath, const TMap<FString, FString>& Placeholders)
{
	FString ResultPath = DirectoryPath;
	for (const TTuple<FString, FString>& Placeholder : Placeholders)
	{
		ResultPath = ResultPath.Replace(*Placeholder.Key, *Placeholder.Value, ESearchCase::CaseSensitive);
	}
	return ResultPath;
}

FString UConventionKeeperRule_FolderStructure::NormalizeRelativePath(const FString& InPath)
{
	FString Result = InPath;
	Result.ReplaceInline(TEXT("\\"), TEXT("/"));
	if (!Result.EndsWith(TEXT("/")))
	{
		Result += TEXT("/");
	}
	return Result;
}

bool UConventionKeeperRule_FolderStructure::IsRelevantPath(const FString& ResolvedPath, const TArray<FString>& SelectedPaths)
{
	if (SelectedPaths.IsEmpty())
	{
		return true;
	}

	const FString NormalizedResolvedPath = NormalizeRelativePath(ResolvedPath);
	for (const FString& SelectedPath : SelectedPaths)
	{
		const FString NormalizedSelectedPath = NormalizeRelativePath(SelectedPath);
		if (NormalizedResolvedPath.StartsWith(NormalizedSelectedPath) || NormalizedSelectedPath.StartsWith(NormalizedResolvedPath))
		{
			return true;
		}
	}
	return false;
}

bool UConventionKeeperRule_FolderStructure::DoesDirectoryExist(const FString& DirectoryPath, const TMap<FString, FString>& Placeholders)
{
	FString ResultPath = DirectoryPath;
	for (const TTuple<FString, FString>& Placeholder : Placeholders)
	{
		ResultPath = ResultPath.Replace(*Placeholder.Key, *Placeholder.Value, ESearchCase::CaseSensitive);
	}

	const FString AbsolutePath = FPaths::ProjectDir() / ResultPath;
	return FPaths::DirectoryExists(AbsolutePath);
}

bool UConventionKeeperRule_FolderStructure::CanValidate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const
{
	const FString ResolvedFolderPath = ResolvePlaceholdersForPath(FolderPath.Path, Placeholders);
	return IsRelevantPath(ResolvedFolderPath, SelectedPaths);
}

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
		case EMessageSeverity::PerformanceWarning:
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
			FMessageLog(TEXT("ConventionKeeper")).Message(Severity, Message);
		}
	}
}

void UConventionKeeperRule_FolderStructure::Validate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders)
{
	if (!CanValidate_Implementation(SelectedPaths, Placeholders))
	{
		return;
	}

	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	const bool bDebug = Settings && Settings->bDebug;
	const EMessageSeverity::Type FailureSeverity = RuleSeverityToMessageSeverity(Severity);

	const FString ResolvedBasePath = ResolvePlaceholdersForPath(FolderPath.Path, Placeholders);

	{
		const bool bExists = DoesDirectoryExist(FolderPath.Path, Placeholders);
		if (!bExists)
		{
			LogRuleMessage(FailureSeverity, FText::Format(
				LOCTEXT("FolderMissing", "[{0}] Required folder is missing: "),
				FText::FromName(RuleId)),
				&ResolvedBasePath);
		}
		else if (bDebug)
		{
			LogRuleMessage(EMessageSeverity::Info, FText::Format(
				LOCTEXT("FolderExists", "[{0}] Folder exists: "),
				FText::FromName(RuleId)),
				&ResolvedBasePath, FText::FromString(TEXT(" — OK")));
		}
	}

	for (const FDirectoryPath& RequiredFolder : RequiredFolders)
	{
		const bool bRequiredFolderExists = DoesDirectoryExist(RequiredFolder.Path, Placeholders);
		const FString ResolvedRequired = ResolvePlaceholdersForPath(RequiredFolder.Path, Placeholders);
		if (!bRequiredFolderExists)
		{
			LogRuleMessage(FailureSeverity, FText::Format(
				LOCTEXT("RequiredSubfolderMissing", "[{0}] Required folder is missing: "),
				FText::FromName(RuleId)),
				&ResolvedRequired, FText::Format(LOCTEXT("RequiredSubfolderMissingSuffix", " (under {0})"), FText::FromString(ResolvedBasePath)));
		}
		else if (bDebug)
		{
			LogRuleMessage(EMessageSeverity::Info, FText::Format(
				LOCTEXT("RequiredSubfolderExists", "[{0}] Required folder exists: "),
				FText::FromName(RuleId)),
				&ResolvedRequired, FText::FromString(TEXT(" — OK")));
		}
	}

	if (bOtherFoldersNotAllowed)
	{
		TArray<FString> AllFoldersInThisPath;
		UConventionKeeperBlueprintLibrary::GetDiskFoldersRelativeToRoot(FolderPath.Path, AllFoldersInThisPath);

		for (const FString& Folder : AllFoldersInThisPath)
		{
			bool bFolderAllowed = false;
			for (const FDirectoryPath& RequiredFolder : RequiredFolders)
			{
				if (FPaths::IsSamePath(Folder, RequiredFolder.Path))
				{
					bFolderAllowed = true;
					break;
				}
			}

			if (!bFolderAllowed)
			{
				LogRuleMessage(FailureSeverity, FText::Format(
					LOCTEXT("DisallowedFolder", "[{0}] Folder not allowed in "),
					FText::FromName(RuleId)),
					&ResolvedBasePath, FText::Format(LOCTEXT("DisallowedFolderSuffix", ": {0}"), FText::FromString(Folder)));
			}
		}

		if (bDebug && AllFoldersInThisPath.Num() == 0)
		{
			LogRuleMessage(EMessageSeverity::Info, FText::Format(
				LOCTEXT("NoExtraFolders", "[{0}] No disallowed folders in "),
				FText::FromName(RuleId)),
				&ResolvedBasePath, FText::FromString(TEXT(" — OK")));
		}
	}
}

#undef LOCTEXT_NAMESPACE

#if WITH_EDITOR
void UConventionKeeperRule_FolderStructure::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	ConvertAllPathsToRelativePaths();
}
#endif

void UConventionKeeperRule_FolderStructure::ConvertAllPathsToRelativePaths()
{
	UConventionKeeperBlueprintLibrary::MakePathRelativeToProjectDir(FolderPath.Path);

	for (FDirectoryPath& Dir : RequiredFolders)
	{
		UConventionKeeperBlueprintLibrary::MakePathRelativeToProjectDir(Dir.Path);
	}
}
