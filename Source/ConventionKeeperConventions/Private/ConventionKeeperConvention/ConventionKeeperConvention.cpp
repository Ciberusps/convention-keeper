// Pavel Penkov 2025 All Rights Reserved.

#include "ConventionKeeperConvention/ConventionKeeperConvention.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperConvention)

UConventionKeeperConvention::UConventionKeeperConvention()
{
	Name = TEXT("Convention Keeper");
	Description = FText::FromString(TEXT("Default convention: UE5 Style Guide (v2). Extend this or UE5 Style Guide for your project."));
	DocsLink = TEXT("https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file");
}
