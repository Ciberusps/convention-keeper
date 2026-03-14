// Pavel Penkov 2025 All Rights Reserved.

#include "Rules/ConventionKeeperRule_FolderStructure.h"

#include "ConventionKeeperBlueprintLibrary.h"
#include "ConventionKeeperConvention.h"
#include "Misc/Paths.h"

#define LOCTEXT_NAMESPACE "FConventionKeeperEditorModule"

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

static void LogValidationMessage(const EMessageSeverity::Type Severity, const FText& Message)
{
	if (IsRunningCommandlet())
	{
		const FString Text = Message.ToString();
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
			UE_LOG(LogTemp, Display, TEXT("%s"), *Text);
			break;
		}
	}
	else
	{
		FMessageLog MyMessageLog = FMessageLog(TEXT("ConventionKeeper"));
		MyMessageLog.Message(Severity, Message);
	}
}

void UConventionKeeperRule_FolderStructure::Validate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders)
{
	if (!CanValidate_Implementation(SelectedPaths, Placeholders))
	{
		return;
	}

	if (!IsRunningCommandlet())
	{
		FMessageLog MyMessageLog = FMessageLog(TEXT("ConventionKeeper"));
		MyMessageLog.NewPage(FText::FromString("Starting a new logging session..."));
	}

	TSet<FString> DiscoveredTemplates = UConventionKeeperConvention::ExtractTemplatesFromPath(FolderPath.Path, Placeholders);
	for (const FString& TemplateName : DiscoveredTemplates)
	{
		UE_LOG(LogTemp, Log, TEXT("Found template: %s"), *TemplateName);
	}

	const bool bExists = DoesDirectoryExist(FolderPath.Path, Placeholders);
	LogValidationMessage(
		bExists ? EMessageSeverity::Type::Info : EMessageSeverity::Type::Error,
		FText::Format(LOCTEXT("ConventionKeeperEditor","Path {0} exists? {1}"), FText::FromString(FolderPath.Path), bExists)
	);

	for (const FDirectoryPath& RequiredFolder : RequiredFolders)
	{
		const bool bRequiredFOlderExists = DoesDirectoryExist(RequiredFolder.Path, Placeholders);
		LogValidationMessage(
			bRequiredFOlderExists ? EMessageSeverity::Type::Info : EMessageSeverity::Type::Error,
			FText::Format(LOCTEXT("ConventionKeeperEditor","Path {0} exists? {1}"), FText::FromString(RequiredFolder.Path), bRequiredFOlderExists)
		);
	}

	if (bOtherFoldersNotAllowed)
	{
		TArray<FString> AllFoldersInThisPath = {};
		UConventionKeeperBlueprintLibrary::GetDiskFoldersRelativeToRoot(FolderPath.Path, AllFoldersInThisPath);

		for (const FString& Folder : AllFoldersInThisPath)
		{
			bool bFolderAlreadyInRequiredFolders = false;
			for (const FDirectoryPath& RequiredFolder : RequiredFolders)
			{
				const bool bIsSameFolder = FPaths::IsSamePath(Folder, RequiredFolder.Path);
				if (bIsSameFolder)
				{
					bFolderAlreadyInRequiredFolders = true;
					break;
				}
			}

			if (!bFolderAlreadyInRequiredFolders)
			{
				LogValidationMessage(
					EMessageSeverity::Error,
					FText::Format(LOCTEXT("ConventionKeeperEditor","Other folders not allowed in {0}"), FText::FromString(FolderPath.Path))
				);
			}
		}
	}

	if (!IsRunningCommandlet())
	{
		FMessageLog MyMessageLog = FMessageLog(TEXT("ConventionKeeper"));
		MyMessageLog.Open();
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
