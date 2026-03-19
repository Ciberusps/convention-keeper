// Pavel Penkov 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Internationalization/Text.h"

class UConventionKeeperConvention_Base;
class UConventionKeeperSettings;

/** Per-class coverage and compliance stats. */
struct FConventionCoverageClassStats
{
	FString ClassName;
	int32 Total = 0;
	int32 Covered = 0;
	int32 Compliant = 0;
};

/** Result of convention coverage + compliance analysis. */
struct FConventionCoverageResult
{
	int32 TotalAssets = 0;
	int32 CoveredAssets = 0;
	int32 CompliantAssets = 0;
	TArray<FConventionCoverageClassStats> PerClass;
};

namespace ConventionCoverage
{
	enum class EConventionReportMode : uint8
	{
		CoverageOnly,
		ComplianceOnly,
		CoverageAndCompliance,
	};

	/**
	 * Runs coverage analysis: which assets are covered by at least one Asset Naming or Asset Placement rule.
	 * When SelectedPaths is empty, analyzes full project content (under Content/ProjectName or resolved pattern roots).
	 */
	CONVENTIONKEEPEREDITOR_API FConventionCoverageResult RunAnalysis(
		UConventionKeeperConvention_Base* Convention,
		const UConventionKeeperSettings* Settings,
		const TArray<FString>& SelectedPaths = {});

	/** Posts coverage/compliance result to Message Log "ConventionKeeper" and optionally opens it. */
	CONVENTIONKEEPEREDITOR_API void ReportToMessageLog(
		const FConventionCoverageResult& Result,
		EConventionReportMode Mode = EConventionReportMode::CoverageAndCompliance,
		bool bOpenLog = true);
}
