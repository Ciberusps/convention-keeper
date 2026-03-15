// Pavel Penkov 2025 All Rights Reserved.

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BTDecorator.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UE5StyleGuideRule_AssetNaming_BTDecorator)

UUE5StyleGuideRule_AssetNaming_BTDecorator::UUE5StyleGuideRule_AssetNaming_BTDecorator()
{
	RuleId = FName(TEXT("asset-naming-bt-decorator"));
	DescriptionKey = FName(TEXT("RuleDesc_asset-naming-bt-decorator"));
	FolderPathPattern.Path = TEXT("Content/{ProjectName}");
	AssetClassPaths = { TEXT("/Script/Engine.Blueprint") };
	BlueprintParentClassPaths = { TEXT("/Script/AIModule.BTDecorator_BlueprintBase") };
	Prefix = TEXT("BTDecorator_");
}
