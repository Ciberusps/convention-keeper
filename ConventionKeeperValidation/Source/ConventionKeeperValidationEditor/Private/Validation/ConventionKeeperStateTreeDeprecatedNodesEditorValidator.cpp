// Pavel Penkov 2025 All Rights Reserved.

#include "Validation/ConventionKeeperStateTreeDeprecatedNodesEditorValidator.h"

#include "AssetRegistry/AssetData.h"
#include "Misc/DataValidation.h"
#include "StructUtils/StructView.h"
#include "UObject/Class.h"
#include "UObject/ObjectMacros.h"
#include "UObject/UnrealType.h"

#include "StateTree.h"
#include "StateTreeConditionBase.h"
#include "StateTreeConsiderationBase.h"
#include "StateTreeEvaluatorBase.h"
#include "StateTreeNodeBase.h"
#include "StateTreeTaskBase.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperStateTreeDeprecatedNodesEditorValidator)

namespace
{
	bool IsStateTreeGraphNodeStruct(const UScriptStruct* Struct)
	{
		if (Struct == nullptr)
		{
			return false;
		}
		return Struct->IsChildOf(FStateTreeConditionBase::StaticStruct())
			|| Struct->IsChildOf(FStateTreeTaskBase::StaticStruct())
			|| Struct->IsChildOf(FStateTreeEvaluatorBase::StaticStruct())
			|| Struct->IsChildOf(FStateTreeConsiderationBase::StaticStruct());
	}

	bool IsStructMarkedDeprecated(const UScriptStruct* Struct)
	{
		if (Struct == nullptr)
		{
			return false;
		}
		if (Struct->HasMetaData(TEXT("DeprecatedProperty")))
		{
			return true;
		}
		if (Struct->HasMetaData(TEXT("DeprecatedNode")))
		{
			return true;
		}
		if (Struct->HasMetaData(TEXT("Deprecated")))
		{
			return true;
		}
		return false;
	}

	bool IsClassMarkedDeprecated(const UClass* Class)
	{
		if (Class == nullptr)
		{
			return false;
		}
		if (Class->HasAnyClassFlags(CLASS_Deprecated))
		{
			return true;
		}
		if (Class->HasMetaData(TEXT("DeprecatedProperty")) || Class->HasMetaData(TEXT("DeprecatedNode")))
		{
			return true;
		}
		return false;
	}

	void ScanStructLayoutForDeprecatedProperties(const UScriptStruct* Struct, TSet<const UScriptStruct*>& Visited, TArray<FString>& OutPaths, const FString& Prefix)
	{
		if (Struct == nullptr || Visited.Contains(Struct))
		{
			return;
		}
		Visited.Add(Struct);

		for (TFieldIterator<FProperty> It(Struct, EFieldIteratorFlags::IncludeSuper); It; ++It)
		{
			const FProperty* Prop = *It;
			const FString Path = Prefix.IsEmpty() ? Prop->GetName() : Prefix + TEXT(".") + Prop->GetName();

			if (Prop->HasAnyPropertyFlags(CPF_Deprecated) || Prop->HasMetaData(TEXT("DeprecatedProperty")))
			{
				OutPaths.Add(Path);
			}

			if (const FStructProperty* SP = CastField<FStructProperty>(Prop))
			{
				ScanStructLayoutForDeprecatedProperties(SP->Struct, Visited, OutPaths, Path);
			}
			else if (const FArrayProperty* AP = CastField<FArrayProperty>(Prop))
			{
				if (const FStructProperty* InnerStruct = CastField<FStructProperty>(AP->Inner))
				{
					ScanStructLayoutForDeprecatedProperties(InnerStruct->Struct, Visited, OutPaths, Path + TEXT("[]"));
				}
			}
			else if (const FSetProperty* Sep = CastField<FSetProperty>(Prop))
			{
				if (const FStructProperty* InnerStruct = CastField<FStructProperty>(Sep->ElementProp))
				{
					ScanStructLayoutForDeprecatedProperties(InnerStruct->Struct, Visited, OutPaths, Path + TEXT("{}"));
				}
			}
			else if (const FMapProperty* MP = CastField<FMapProperty>(Prop))
			{
				if (const FStructProperty* KeyStruct = CastField<FStructProperty>(MP->KeyProp))
				{
					ScanStructLayoutForDeprecatedProperties(KeyStruct->Struct, Visited, OutPaths, Path + TEXT("[key]"));
				}
				if (const FStructProperty* ValueStruct = CastField<FStructProperty>(MP->ValueProp))
				{
					ScanStructLayoutForDeprecatedProperties(ValueStruct->Struct, Visited, OutPaths, Path + TEXT("[value]"));
				}
			}
			else if (const FObjectPropertyBase* ObjProp = CastField<FObjectPropertyBase>(Prop))
			{
				if (IsClassMarkedDeprecated(ObjProp->PropertyClass))
				{
					OutPaths.Add(FString::Printf(TEXT("%s (object class %s)"), *Path, *ObjProp->PropertyClass->GetName()));
				}
			}
		}
	}

	void ReportDeprecatedStructLayout(
		UEditorValidatorBase* Validator,
		const UObject* Asset,
		const TCHAR* ScopeLabel,
		const UScriptStruct* Struct)
	{
		if (Struct == nullptr || Validator == nullptr)
		{
			return;
		}
		TSet<const UScriptStruct*> Visited;
		TArray<FString> Paths;
		ScanStructLayoutForDeprecatedProperties(Struct, Visited, Paths, FString());
		for (const FString& Path : Paths)
		{
			Validator->AssetFails(Asset, FText::Format(
				NSLOCTEXT("ConventionKeeperValidationEditor", "StateTreeDeprecatedProperty", "StateTree {0}: deprecated field or reference on type '{1}': {2}"),
				FText::FromString(ScopeLabel),
				FText::FromString(Struct->GetName()),
				FText::FromString(Path)));
		}
	}
}

bool UConventionKeeperStateTreeDeprecatedNodesEditorValidator::CanValidateAsset_Implementation(
	const FAssetData& InAssetData,
	UObject* InObject,
	FDataValidationContext& InContext) const
{
	return InObject != nullptr && InObject->IsA<UStateTree>();
}

EDataValidationResult UConventionKeeperStateTreeDeprecatedNodesEditorValidator::ValidateLoadedAsset_Implementation(
	const FAssetData& InAssetData,
	UObject* InAsset,
	FDataValidationContext& Context)
{
	UStateTree* StateTree = Cast<UStateTree>(InAsset);
	if (StateTree == nullptr)
	{
		return EDataValidationResult::Valid;
	}

	const FInstancedStructContainer& Nodes = StateTree->GetNodes();
	for (int32 NodeIndex = 0; NodeIndex < Nodes.Num(); ++NodeIndex)
	{
		const FConstStructView NodeView = Nodes[NodeIndex];
		const UScriptStruct* NodeStruct = NodeView.GetScriptStruct();
		if (NodeStruct == nullptr || !NodeView.IsValid())
		{
			continue;
		}
		if (!IsStateTreeGraphNodeStruct(NodeStruct))
		{
			continue;
		}

		const FString NodeLabel = FString::Printf(TEXT("node[%d] %s"), NodeIndex, *NodeStruct->GetName());

		if (IsStructMarkedDeprecated(NodeStruct))
		{
			const FString* DeprecationMessage = NodeStruct->FindMetaData(TEXT("DeprecationMessage"));
			const FText Detail = DeprecationMessage != nullptr && !DeprecationMessage->IsEmpty()
				? FText::FromString(*DeprecationMessage)
				: FText::GetEmpty();
			if (Detail.IsEmpty())
			{
				AssetFails(InAsset, FText::Format(
					NSLOCTEXT("ConventionKeeperValidationEditor", "StateTreeDeprecatedNodeStruct", "StateTree {0}: node struct is deprecated."),
					FText::FromString(NodeLabel)));
			}
			else
			{
				AssetFails(InAsset, FText::Format(
					NSLOCTEXT("ConventionKeeperValidationEditor", "StateTreeDeprecatedNodeStructMsg", "StateTree {0}: node struct is deprecated — {1}"),
					FText::FromString(NodeLabel),
					Detail));
			}
		}

		ReportDeprecatedStructLayout(this, InAsset, *NodeLabel, NodeStruct);

		const FStateTreeNodeBase* NodeBase = NodeView.GetPtr<const FStateTreeNodeBase>();
		if (NodeBase != nullptr)
		{
			const UStruct* InstanceType = NodeBase->GetInstanceDataType();
			const UScriptStruct* InstanceStruct = Cast<UScriptStruct>(InstanceType);
			if (InstanceStruct != nullptr && InstanceStruct != NodeStruct)
			{
				const FString InstanceLabel = NodeLabel + TEXT(" instance data");
				if (IsStructMarkedDeprecated(InstanceStruct))
				{
					const FString* DeprecationMessage = InstanceStruct->FindMetaData(TEXT("DeprecationMessage"));
					const FText Detail = DeprecationMessage != nullptr && !DeprecationMessage->IsEmpty()
						? FText::FromString(*DeprecationMessage)
						: FText::GetEmpty();
					if (Detail.IsEmpty())
					{
						AssetFails(InAsset, FText::Format(
							NSLOCTEXT("ConventionKeeperValidationEditor", "StateTreeDeprecatedInstanceStruct", "StateTree {0}: instance data type '{1}' is deprecated."),
							FText::FromString(InstanceLabel),
							FText::FromString(InstanceStruct->GetName())));
					}
					else
					{
						AssetFails(InAsset, FText::Format(
							NSLOCTEXT("ConventionKeeperValidationEditor", "StateTreeDeprecatedInstanceStructMsg", "StateTree {0}: instance data type '{1}' is deprecated — {2}"),
							FText::FromString(InstanceLabel),
							FText::FromString(InstanceStruct->GetName()),
							Detail));
					}
				}
				ReportDeprecatedStructLayout(this, InAsset, *InstanceLabel, InstanceStruct);
			}
		}
	}

	return EDataValidationResult::Valid;
}
