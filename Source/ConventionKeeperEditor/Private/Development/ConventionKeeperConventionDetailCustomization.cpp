// Pavel Penkov 2025 All Rights Reserved.

#include "Development/ConventionKeeperConventionDetailCustomization.h"
#include "ConventionKeeperConvention_Base.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "HAL/PlatformProcess.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "ConventionKeeperConventionDetailCustomization"

TSharedRef<IDetailCustomization> FConventionKeeperConventionDetailCustomization::MakeInstance()
{
	return MakeShareable(new FConventionKeeperConventionDetailCustomization);
}

void FConventionKeeperConventionDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailBuilder.GetObjectsBeingCustomized(Objects);
	if (Objects.Num() == 0 || !Objects[0].IsValid())
	{
		return;
	}
	UConventionKeeperConvention_Base* Convention = Cast<UConventionKeeperConvention_Base>(Objects[0].Get());
	if (!Convention)
	{
		return;
	}

	IDetailCategoryBuilder& DocCategory = DetailBuilder.EditCategory(
		TEXT("Docs"),
		FText::GetEmpty(),
		ECategoryPriority::Important);

	DocCategory.AddCustomRow(LOCTEXT("OpenDocRowLabel", "Open in browser"))
		.NameContent()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("OpenDocRowName", "Docs"))
			.Font(IDetailLayoutBuilder::GetDetailFont())
		]
		.ValueContent()
		.MinDesiredWidth(200.f)
		[
			SNew(SButton)
			.HAlign(HAlign_Center)
			.IsEnabled_Lambda([Convention]() { return Convention && !Convention->GetConventionDocumentationUrlForDisplay().IsEmpty(); })
			.Text(LOCTEXT("OpenConventionDocButton", "Open documentation"))
			.ToolTipText(LOCTEXT(
				"OpenConventionDocTooltip",
				"Opens the convention markdown page in your browser (GitHub blob URL from project documentation settings)."))
			.OnClicked_Lambda([Convention]()
			{
				const FString Url = Convention->GetConventionDocumentationUrlForDisplay();
				if (!Url.IsEmpty())
				{
					FPlatformProcess::LaunchURL(*Url, nullptr, nullptr);
				}
				return FReply::Handled();
			})
		];
}

#undef LOCTEXT_NAMESPACE
