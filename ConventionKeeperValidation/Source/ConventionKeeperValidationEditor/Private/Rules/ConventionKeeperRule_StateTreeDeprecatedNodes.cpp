// Pavel Penkov 2025 All Rights Reserved.

#include "Rules/ConventionKeeperRule_StateTreeDeprecatedNodes.h"

#include "StateTree.h"
#include "Validation/ConventionKeeperStateTreeDeprecatedNodesEditorValidator.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperRule_StateTreeDeprecatedNodes)

UConventionKeeperRule_StateTreeDeprecatedNodes::UConventionKeeperRule_StateTreeDeprecatedNodes(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	EditorValidatorClass = UConventionKeeperStateTreeDeprecatedNodesEditorValidator::StaticClass();
	LimitToAssetTypes.Reset();
	LimitToAssetTypes.Add(UStateTree::StaticClass());
}
