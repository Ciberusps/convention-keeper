// Pavel Penkov 2025 All Rights Reserved.

#include "Details/ConventionKeeperRuleDetailsCustomization.h"

#include "Rules/ConventionKeeperRule.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "HAL/PlatformProcess.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "ConventionKeeperRuleDetails"

TSharedRef<IDetailCustomization> FConventionKeeperRuleDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FConventionKeeperRuleDetailsCustomization());
}

void FConventionKeeperRuleDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailBuilder.GetObjectsBeingCustomized(Objects);
	if (Objects.Num() == 0)
	{
		return;
	}

	UConventionKeeperRule* Rule = Cast<UConventionKeeperRule>(Objects[0].Get());
	if (!Rule)
	{
		return;
	}

	const FString DocUrl = Rule->GetDocumentationUrl();

	IDetailCategoryBuilder& DocCategory = DetailBuilder.EditCategory(
		TEXT("Documentation"),
		LOCTEXT("DocumentationCategory", "Documentation"),
		ECategoryPriority::Important);

	DocCategory.AddCustomRow(LOCTEXT("DocLinkRow", "Rule documentation"))
		.WholeRowContent()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(0.f, 2.f)
				[
					SNew(SButton)
						.Text(LOCTEXT("OpenDocumentation", "Open documentation in browser"))
						.OnClicked_Lambda([DocUrl]()
						{
							if (!DocUrl.IsEmpty())
							{
								FPlatformProcess::LaunchURL(*DocUrl, nullptr, nullptr);
							}
							return FReply::Handled();
						})
						.IsEnabled(!DocUrl.IsEmpty())
						.ToolTipText(DocUrl.IsEmpty()
							? LOCTEXT("DocUrlNotSetTooltip", "Set \"Documentation repository URL\" in Project Settings → Convention Keeper to enable links.")
							: FText::FromString(DocUrl))
				]
			+ SHorizontalBox::Slot()
				.FillWidth(1.f)
				.Padding(8.f, 0.f)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
						.Text(DocUrl.IsEmpty()
							? LOCTEXT("DocUrlNotSet", "Documentation URL not configured.")
							: FText::FromString(DocUrl))
						.AutoWrapText(true)
						.IsEnabled(DocUrl.IsEmpty())
				]
		];
}

#undef LOCTEXT_NAMESPACE
