// Pavel Penkov 2025 All Rights Reserved.

#include "Rules/ConventionKeeperRule.h"

#include "ConventionKeeperConvention.h"
#include "Development/ConventionKeeperSettings.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Localization/ConventionKeeperLocalization.h"
#include "Async/Async.h"
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
	const FString RawUrl = GetDocumentationRawUrl();
	if (RawUrl.IsEmpty())
	{
		DocumentationContent = TEXT("—");
		return;
	}
	TWeakObjectPtr<UConventionKeeperRule> WeakThis(this);
	TSharedPtr<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(RawUrl);
	Request->SetVerb(TEXT("GET"));
	Request->OnProcessRequestComplete().BindLambda(
		[WeakThis](FHttpRequestPtr, FHttpResponsePtr Response, bool bSuccess)
		{
			FString Content;
			if (bSuccess && Response.IsValid() && Response->GetResponseCode() == 200)
			{
				Content = Response->GetContentAsString();
			}
			else
			{
				Content = TEXT("Could not load. Open the URL above in a browser.");
			}
			AsyncTask(ENamedThreads::GameThread, [WeakThis, Content]()
			{
				if (UConventionKeeperRule* Rule = WeakThis.Get())
				{
					Rule->DocumentationContent = Content;
				}
			});
		});
	Request->ProcessRequest();
}
#endif
