// Pavel Penkov 2025 All Rights Reserved.

#include "Development/ConventionKeeperSettingsCustomization.h"
#include "Development/ConventionKeeperSettings.h"
#include "ConventionCoverage.h"
#include "ConventionKeeperConvention_Base.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Logging/MessageLog.h"

#define LOCTEXT_NAMESPACE "ConventionKeeperSettingsCustomization"

TSharedRef<IDetailCustomization> FConventionKeeperSettingsCustomization::MakeInstance()
{
	return MakeShareable(new FConventionKeeperSettingsCustomization);
}

void FConventionKeeperSettingsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailBuilder.GetObjectsBeingCustomized(Objects);
	if (Objects.Num() == 0)
	{
		return;
	}

	UConventionKeeperSettings* Settings = Cast<UConventionKeeperSettings>(Objects[0].Get());
	if (!Settings)
	{
		return;
	}

	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Convention Coverage", LOCTEXT("CoverageCategory", "Convention Coverage & Compliance"));
	Category.AddCustomRow(FText::GetEmpty())
		.WholeRowContent()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(0, 4)
			[
				SNew(SButton)
				.Text(LOCTEXT("RunCoverageReport", "Run coverage report"))
				.ToolTipText(LOCTEXT("RunCoverageReportTooltip", "Run rule coverage report (which assets have at least one rule); results in Message Log."))
				.OnClicked_Lambda([Settings]()
				{
					UConventionKeeperConvention_Base* Convention = Settings->GetResolvedConvention();
					if (!Convention)
					{
						FMessageLog(TEXT("ConventionKeeper")).Error(LOCTEXT("NoConventionCoverage", "Convention is not set. Set Convention or Convention Asset above."));
						FMessageLog(TEXT("ConventionKeeper")).Open(EMessageSeverity::Error, true);
						return FReply::Handled();
					}
					FConventionCoverageResult Result = ConventionCoverage::RunAnalysis(Convention, Settings, TArray<FString>());
					ConventionCoverage::ReportToMessageLog(Result, ConventionCoverage::EConventionReportMode::CoverageOnly, true);
					return FReply::Handled();
				})
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(8, 4, 0, 4)
			[
				SNew(SButton)
				.Text(LOCTEXT("RunComplianceReport", "Run compliance report"))
				.ToolTipText(LOCTEXT("RunComplianceReportTooltip", "Run compliance report (covered assets passing validation); results in Message Log."))
				.OnClicked_Lambda([Settings]()
				{
					UConventionKeeperConvention_Base* Convention = Settings->GetResolvedConvention();
					if (!Convention)
					{
						FMessageLog(TEXT("ConventionKeeper")).Error(LOCTEXT("NoConventionCoverage", "Convention is not set. Set Convention or Convention Asset above."));
						FMessageLog(TEXT("ConventionKeeper")).Open(EMessageSeverity::Error, true);
						return FReply::Handled();
					}
					FConventionCoverageResult Result = ConventionCoverage::RunAnalysis(Convention, Settings, TArray<FString>());
					ConventionCoverage::ReportToMessageLog(Result, ConventionCoverage::EConventionReportMode::ComplianceOnly, true);
					return FReply::Handled();
				})
			]
		];
}

#undef LOCTEXT_NAMESPACE
