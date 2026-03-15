// Pavel Penkov 2025 All Rights Reserved.

#include "Rules/ConventionKeeperRule.h"

#include "ConventionKeeperConvention.h"
#include "Development/ConventionKeeperSettings.h"
#include "Localization/ConventionKeeperLocalization.h"
#include "Interfaces/IPluginManager.h"
#include "Logging/MessageLog.h"
#include "Logging/TokenizedMessage.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperRule)

FText UConventionKeeperRule::GetDisplayDescription(const UConventionKeeperConvention* Convention) const
{
	if (Convention)
	{
		FText Loc = Convention->GetLocalizedRuleDescription(RuleId);
		if (!Loc.IsEmpty())
		{
			return Loc;
		}
	}
	if (!DescriptionKey.IsNone())
	{
		return ConventionKeeperLoc::GetText(DescriptionKey);
	}
	return Description;
}

FString UConventionKeeperRule::GetDocumentationUrl() const
{
	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	if (!Settings || Settings->DocsRepositoryUrl.IsEmpty())
	{
		return FString();
	}
	FString Path = DocPathOverride;
	if (Path.IsEmpty())
	{
		if (RuleId.IsNone())
		{
			return FString();
		}
		Path = Settings->DocsRulePathTemplate;
		Path.ReplaceInline(TEXT("{RuleId}"), *RuleId.ToString());
	}
	FString Base = Settings->DocsRepositoryUrl;
	while (Base.EndsWith(TEXT("/")))
	{
		Base.LeftChopInline(1);
	}
	FString Branch = Settings->DocsBranch.IsEmpty() ? TEXT("main") : Settings->DocsBranch;
	return FString::Printf(TEXT("%s/blob/%s/%s"), *Base, *Branch, *Path);
}

FString UConventionKeeperRule::GetDocumentationUrlForDisplay() const
{
	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	if (!Settings || Settings->DocsRepositoryUrl.IsEmpty() || RuleId.IsNone())
	{
		return GetDocumentationUrl();
	}
	auto ResolveDocPath = [](const FString& RelPath, FString& OutAbsolutePath) -> bool
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
				FString PluginPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(Plugin->GetBaseDir(), RelPath));
				if (FPaths::FileExists(PluginPath))
				{
					OutAbsolutePath = MoveTemp(PluginPath);
					return true;
				}
			}
		}
		return false;
	};
	FString RelPathBase = DocPathOverride.IsEmpty()
		? Settings->DocsRulePathTemplate.Replace(TEXT("{RuleId}"), *RuleId.ToString())
		: DocPathOverride;
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
		if (ResolveDocPath(RelPath, LocalPath))
		{
			ResolvedRelPath = RelPath;
			break;
		}
	}
	if (ResolvedRelPath.IsEmpty())
	{
		return GetDocumentationUrl();
	}
	FString Base = Settings->DocsRepositoryUrl;
	while (Base.EndsWith(TEXT("/")))
	{
		Base.LeftChopInline(1);
	}
	FString Branch = Settings->DocsBranch.IsEmpty() ? TEXT("main") : Settings->DocsBranch;
	return FString::Printf(TEXT("%s/blob/%s/%s"), *Base, *Branch, *ResolvedRelPath);
}

FString UConventionKeeperRule::GetDocumentationRawUrl() const
{
	FString BlobUrl = GetDocumentationUrl();
	if (BlobUrl.IsEmpty())
	{
		return FString();
	}
	FString Raw = BlobUrl;
	if (!Raw.ReplaceInline(TEXT("github.com"), TEXT("raw.githubusercontent.com")))
	{
		return FString();
	}
	if (!Raw.ReplaceInline(TEXT("/blob/"), TEXT("/")))
	{
		return FString();
	}
	return Raw;
}

bool UConventionKeeperRule::CanValidate_Implementation(const TArray<FString>& /*SelectedPaths*/, const TMap<FString, FString>& /*Placeholders*/) const
{
	return true;
}

void UConventionKeeperRule::Validate_Implementation(const TArray<FString>& /*SelectedPaths*/, const TMap<FString, FString>& /*Placeholders*/)
{
}

FString UConventionKeeperRule::NormalizeRelativePath(const FString& InPath)
{
	FString Result = InPath;
	Result.ReplaceInline(TEXT("\\"), TEXT("/"));
	if (!Result.EndsWith(TEXT("/")))
	{
		Result += TEXT("/");
	}
	return Result;
}

#if WITH_EDITOR
void UConventionKeeperRule::PostLoad()
{
	Super::PostLoad();
	RefreshDocumentationFields();
}

void UConventionKeeperRule::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	const FName PropName = PropertyChangedEvent.GetPropertyName();
	if (PropName == GET_MEMBER_NAME_CHECKED(UConventionKeeperRule, RuleId)
		|| PropName == GET_MEMBER_NAME_CHECKED(UConventionKeeperRule, DocPathOverride))
	{
		RefreshDocumentationFields();
	}
}

void UConventionKeeperRule::RefreshDocumentationFields()
{
	DocumentationUrl = GetDocumentationUrl();
	DocumentationContent.Empty();

	const UConventionKeeperSettings* Settings = GetDefault<UConventionKeeperSettings>();
	if (!Settings || RuleId.IsNone())
	{
		DocumentationContent = TEXT("View at link only.");
		return;
	}

	auto ResolveDocPath = [](const FString& RelPath, FString& OutAbsolutePath) -> bool
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
				FString PluginPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(Plugin->GetBaseDir(), RelPath));
				if (FPaths::FileExists(PluginPath))
				{
					OutAbsolutePath = MoveTemp(PluginPath);
					return true;
				}
			}
		}
		return false;
	};

	FString RelPathBase = DocPathOverride.IsEmpty()
		? Settings->DocsRulePathTemplate.Replace(TEXT("{RuleId}"), *RuleId.ToString())
		: DocPathOverride;
	const FString Dir = FPaths::GetPath(RelPathBase);
	const FString BaseName = FPaths::GetBaseFilename(RelPathBase, true);
	const FString Ext = FPaths::GetExtension(RelPathBase, true);
	const FString Lang = Settings->GetEffectiveLanguageCode();

	TArray<FString> PathsToTry;
	if (!Lang.IsEmpty())
	{
		PathsToTry.Add(FPaths::Combine(Dir, Lang, BaseName + Ext));
	}
	PathsToTry.Add(RelPathBase);

	FString LocalPath;
	for (const FString& RelPath : PathsToTry)
	{
		if (ResolveDocPath(RelPath, LocalPath))
		{
			break;
		}
	}
	if (!FPaths::FileExists(LocalPath))
	{
		DocumentationContent = TEXT("View at link only.");
		return;
	}

	FString Content;
	if (FFileHelper::LoadFileToString(Content, *LocalPath))
	{
		DocumentationContent = MoveTemp(Content);
	}
	else
	{
		DocumentationContent = TEXT("View at link only.");
	}
}

void UConventionKeeperRule::LogRuleMessage(const UConventionKeeperRule* Rule, EMessageSeverity::Type Severity, const FText& MessageBody, const FString* PathForLink, const FText& Suffix)
{
	if (IsRunningCommandlet())
	{
		FString Prefix = Rule && !Rule->RuleId.IsNone() ? FString::Printf(TEXT("[%s] "), *Rule->RuleId.ToString()) : TEXT("[?] ");
		FString Text = Prefix + MessageBody.ToString();
		if (PathForLink && !PathForLink->IsEmpty())
		{
			Text += TEXT(" ");
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
		return;
	}
	TSharedRef<FTokenizedMessage> TokenizedMessage = FTokenizedMessage::Create(Severity);
	if (Rule && !Rule->RuleId.IsNone())
	{
		FString DocUrl = Rule->GetDocumentationUrlForDisplay();
		TokenizedMessage->AddToken(FTextToken::Create(FText::FromString(TEXT("["))));
		if (!DocUrl.IsEmpty())
		{
			TokenizedMessage->AddToken(FURLToken::Create(DocUrl, FText::FromName(Rule->RuleId)));
		}
		else
		{
			TokenizedMessage->AddToken(FTextToken::Create(FText::FromName(Rule->RuleId)));
		}
		TokenizedMessage->AddToken(FTextToken::Create(FText::FromString(TEXT("] "))));
	}
	TokenizedMessage->AddToken(FTextToken::Create(MessageBody));
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
		TokenizedMessage->AddToken(FAssetNameToken::Create(AssetPath, FText::FromString(*AssetPath)));
	}
	if (!Suffix.IsEmpty())
	{
		TokenizedMessage->AddToken(FTextToken::Create(Suffix));
	}
	FMessageLog(TEXT("ConventionKeeper")).AddMessage(TokenizedMessage);
}
#endif
