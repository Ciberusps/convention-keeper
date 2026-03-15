// Pavel Penkov 2025 All Rights Reserved.

#include "Rules/ConventionKeeperRule_NamingConvention.h"

#include "AssetRegistry/ARFilter.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "ConventionKeeperBlueprintLibrary.h"
#include "Development/ConventionKeeperSettings.h"
#include "Logging/MessageLog.h"
#include "Logging/TokenizedMessage.h"
#include "Localization/ConventionKeeperLocalization.h"
#include "Misc/Paths.h"
#include "Rules/ConventionKeeperRule.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperRule_NamingConvention)

FString UConventionKeeperRule_NamingConvention::NormalizeRelativePath(const FString& InPath)
{
	return UConventionKeeperRule::NormalizeRelativePath(InPath);
}

namespace NamingConventionPathHelpers
{
static FString SelectedPathAsContentForm(const FString& InPath)
{
	FString Path = InPath;
	Path.ReplaceInline(TEXT("\\"), TEXT("/"));
	Path.TrimStartAndEndInline();
	const FString ProjectDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()).Replace(TEXT("\\"), TEXT("/"));
	if (Path.StartsWith(ProjectDir))
	{
		Path = Path.Mid(ProjectDir.Len());
	}
	else
	{
		const FString ContentMarker = TEXT("/Content/");
		const int32 ContentPos = Path.Find(ContentMarker);
		if (ContentPos != INDEX_NONE)
		{
			Path = FString(TEXT("Content/")) + Path.Mid(ContentPos + ContentMarker.Len());
		}
	}
	while (Path.StartsWith(TEXT("/")))
	{
		Path.RemoveFromStart(TEXT("/"));
	}
	if (Path.StartsWith(TEXT("All/")))
	{
		Path.RemoveFromStart(TEXT("All/"));
	}
	if (Path.StartsWith(TEXT("Game/")))
	{
		Path = FString(TEXT("Content/")) + Path.Mid(5);
	}
	const int32 DotPos = Path.Find(TEXT("."), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	if (DotPos != INDEX_NONE)
	{
		const FString Ext = Path.Mid(DotPos + 1).ToLower();
		if (Ext == TEXT("uasset") || Ext == TEXT("umap"))
		{
			Path = Path.Left(DotPos);
		}
	}
	if (!Path.EndsWith(TEXT("/")))
	{
		Path += TEXT("/");
	}
	return Path;
}
}

bool UConventionKeeperRule_NamingConvention::IsRelevantPath(const FString& ResolvedPath, const TArray<FString>& SelectedPaths)
{
	return IsRelevantPath(TArray<FString>{NormalizeRelativePath(ResolvedPath)}, SelectedPaths);
}

bool UConventionKeeperRule_NamingConvention::IsRelevantPath(const TArray<FString>& ResolvedPathsToCheck, const TArray<FString>& SelectedPaths)
{
	if (SelectedPaths.IsEmpty())
	{
		return true;
	}
	for (const FString& ResolvedPath : ResolvedPathsToCheck)
	{
		FString PathForCompare = ResolvedPath;
		PathForCompare.ReplaceInline(TEXT("\\"), TEXT("/"));
		while (PathForCompare.StartsWith(TEXT("/")))
		{
			PathForCompare.RemoveFromStart(TEXT("/"));
		}
		const FString NormalizedResolvedPath = NormalizeRelativePath(PathForCompare);
		for (const FString& SelectedPath : SelectedPaths)
		{
			const FString NormalizedSelectedPath = NamingConventionPathHelpers::SelectedPathAsContentForm(SelectedPath);
			if (NormalizedResolvedPath.StartsWith(NormalizedSelectedPath) || NormalizedSelectedPath.StartsWith(NormalizedResolvedPath))
			{
				return true;
			}
		}
	}
	return false;
}

bool UConventionKeeperRule_NamingConvention::IsPathUnderExcluded(const FString& ResolvedPath, const TArray<FString>& Exclusions, const TMap<FString, FString>& Placeholders)
{
	const FString NormalizedPath = NormalizeRelativePath(ResolvedPath);
	for (const FString& Exclusion : Exclusions)
	{
		FString ResolvedExclude = Exclusion;
		for (const TTuple<FString, FString>& Pair : Placeholders)
		{
			ResolvedExclude = ResolvedExclude.Replace(*Pair.Key, *Pair.Value, ESearchCase::CaseSensitive);
		}
		ResolvedExclude.ReplaceInline(TEXT("\\"), TEXT("/"));
		ResolvedExclude.TrimStartAndEndInline();
		const bool bExclusionIsFolder = ResolvedExclude.EndsWith(TEXT("/"));
		FString NormalizedExclude = bExclusionIsFolder ? NormalizeRelativePath(ResolvedExclude) : ResolvedExclude;
		if (bExclusionIsFolder)
		{
			if (NormalizedPath.StartsWith(NormalizedExclude) || NormalizedExclude.StartsWith(NormalizedPath))
			{
				return true;
			}
		}
		else
		{
			if (NormalizedPath == NormalizedExclude + TEXT("/") || NormalizedPath.StartsWith(NormalizedExclude + TEXT("/")))
			{
				return true;
			}
		}
	}
	return false;
}

namespace NamingConventionRuleHelpers
{
static EMessageSeverity::Type SeverityToMessage(EConventionRuleSeverity RuleSeverity)
{
	return RuleSeverity == EConventionRuleSeverity::Warning ? EMessageSeverity::Warning : EMessageSeverity::Error;
}

static void LogMessage(EMessageSeverity::Type Severity, const FText& Message, const FString* PathForLink = nullptr)
{
	if (IsRunningCommandlet())
	{
		FString Text = Message.ToString();
		if (PathForLink && !PathForLink->IsEmpty())
		{
			Text += TEXT(" ");
			Text += *PathForLink;
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
			TokenizedMessage->AddToken(FAssetNameToken::Create(AssetPath, FText::FromString(*AssetPath)));
			FMessageLog(TEXT("ConventionKeeper")).AddMessage(TokenizedMessage);
		}
		else
		{
			FMessageLog(TEXT("ConventionKeeper")).Message(Severity, Message);
		}
	}
}
}

bool UConventionKeeperRule_NamingConvention::CanValidate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders) const
{
	FString PatternPath = FolderPathPattern.Path;
	PatternPath.ReplaceInline(TEXT("\\"), TEXT("/"));
	PatternPath.TrimStartAndEndInline();
	if (PatternPath.IsEmpty())
	{
		PatternPath = TEXT("Content/{ProjectName}");
	}
	FString ResolvedFolderPath = PatternPath;
	for (const TTuple<FString, FString>& Pair : Placeholders)
	{
		ResolvedFolderPath = ResolvedFolderPath.Replace(*Pair.Key, *Pair.Value, ESearchCase::CaseSensitive);
	}
	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	if (Settings && IsPathUnderExcluded(NormalizeRelativePath(ResolvedFolderPath), Settings->Exclusions, Placeholders))
	{
		return false;
	}
	TMap<FString, FString> PlaceholdersWithBraces = Settings ? Settings->GetPlaceholders() : TMap<FString, FString>();
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
	if (ResolvedPaths.Num() == 0 && !PatternPath.Contains(TEXT("{")))
	{
		FString SinglePath = PatternPath;
		for (const TTuple<FString, FString>& Pair : PlaceholdersWithBraces)
		{
			SinglePath = SinglePath.Replace(*Pair.Key, *Pair.Value, ESearchCase::CaseSensitive);
		}
		SinglePath = NormalizeRelativePath(SinglePath);
		if (!SinglePath.IsEmpty())
		{
			ResolvedPaths.Add(SinglePath);
		}
	}
	return IsRelevantPath(ResolvedPaths, SelectedPaths);
}

void UConventionKeeperRule_NamingConvention::Validate_Implementation(const TArray<FString>& SelectedPaths, const TMap<FString, FString>& Placeholders)
{
	if (!CanValidate_Implementation(SelectedPaths, Placeholders))
	{
		return;
	}

	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	const EMessageSeverity::Type FailureSeverity = NamingConventionRuleHelpers::SeverityToMessage(Severity);

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
	TMap<FString, FString> PlaceholdersWithBraces = Settings ? Settings->GetPlaceholders() : TMap<FString, FString>();
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
				ResolvedPaths.Add(SinglePath);
			}
		}
	}

	TArray<FString> BasePathsToValidate;
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
		const FString Norm = NormalizeRelativePath(ResolvedPath);
		if (SelectedPaths.IsEmpty())
		{
			BasePathsToValidate.AddUnique(Norm);
			continue;
		}
		for (const FString& SelectedPath : SelectedPaths)
		{
			const FString NormSelected = NamingConventionPathHelpers::SelectedPathAsContentForm(SelectedPath);
			if (NormSelected.StartsWith(Norm))
			{
				BasePathsToValidate.AddUnique(Norm);
				break;
			}
			if (Norm.StartsWith(NormSelected))
			{
				BasePathsToValidate.AddUnique(NormSelected);
				break;
			}
		}
	}

	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();

	for (const FString& BasePath : BasePathsToValidate)
	{
		if (Settings && IsPathUnderExcluded(BasePath, Settings->Exclusions, PlaceholdersWithBraces))
		{
			continue;
		}

		auto ValidateFolderNameRecursive = [this, &FailureSeverity, &PlaceholdersWithBraces, Settings](
			const FString& FolderPath,
			auto& Self) -> void
		{
			TArray<FString> DirectChildren;
			UConventionKeeperBlueprintLibrary::GetDiskFoldersRelativeToRoot(FolderPath, DirectChildren);
			for (const FString& ChildPath : DirectChildren)
			{
				int32 LastSlash = INDEX_NONE;
				for (int32 i = ChildPath.Len() - 1; i >= 0; --i)
				{
					if (ChildPath[i] == TEXT('/'))
					{
						LastSlash = i;
						break;
					}
				}
				const FString SegmentName = LastSlash >= 0 ? ChildPath.Mid(LastSlash + 1) : ChildPath;
				if (SegmentName.IsEmpty())
				{
					continue;
				}
				if (Settings && IsPathUnderExcluded(ChildPath, Settings->Exclusions, PlaceholdersWithBraces))
				{
					continue;
				}
				if (!IsNameValidForFolder(SegmentName))
				{
					NamingConventionRuleHelpers::LogMessage(FailureSeverity,
						FText::Format(
							ConventionKeeperLoc::GetText(FName(TEXT("NamingConventionFolder"))),
							FText::FromName(RuleId),
							FText::FromString(SegmentName)),
						&ChildPath);
				}
				Self(ChildPath, Self);
			}
		};

		int32 BasePathLastSlash = INDEX_NONE;
		for (int32 i = BasePath.Len() - 1; i >= 0; --i)
		{
			if (BasePath[i] == TEXT('/'))
			{
				BasePathLastSlash = i;
				break;
			}
		}
		const FString BaseSegmentName = BasePathLastSlash >= 0 ? BasePath.Mid(BasePathLastSlash + 1) : BasePath;
		if (!BaseSegmentName.IsEmpty() && !IsNameValidForFolder(BaseSegmentName))
		{
			NamingConventionRuleHelpers::LogMessage(FailureSeverity,
				FText::Format(
					ConventionKeeperLoc::GetText(FName(TEXT("NamingConventionFolder"))),
					FText::FromName(RuleId),
					FText::FromString(BaseSegmentName)),
				&BasePath);
		}

		ValidateFolderNameRecursive(BasePath, ValidateFolderNameRecursive);

		FString PackagePath = FString(TEXT("/Game/")) + BasePath.Mid(8);
		if (PackagePath.EndsWith(TEXT("/")))
		{
			PackagePath.LeftChopInline(1);
		}

		FARFilter Filter;
		Filter.PackagePaths.Add(FName(*PackagePath));
		Filter.bRecursivePaths = true;

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
			if (Settings && IsPathUnderExcluded(RelativePath, Settings->Exclusions, PlaceholdersWithBraces))
			{
				continue;
			}
			if (!IsNameValidForAsset(AssetName))
			{
				NamingConventionRuleHelpers::LogMessage(FailureSeverity,
					FText::Format(
						ConventionKeeperLoc::GetText(FName(TEXT("NamingConventionAsset"))),
						FText::FromName(RuleId),
						FText::FromString(AssetName)),
					&RelativePath);
			}
		}
	}
}
