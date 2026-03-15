// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/UE5StyleGuideConvention.h"
#include "Rules/ConventionKeeperRule_NamingConvention_PascalCase.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideConvention)

UUE5StyleGuideConvention::UUE5StyleGuideConvention()
{
	Name = TEXT("UE5 Style Guide");
	Rules.Add(CreateDefaultSubobject<UConventionKeeperRule_NamingConvention_PascalCase>(TEXT("Rule_NamingConvention_PascalCase")));
}
