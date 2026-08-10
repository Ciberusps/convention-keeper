# state-tree-deprecated-nodes

**Engine classes:** `UConventionKeeperRule_StateTreeDeprecatedNodes`, `UConventionKeeperStateTreeDeprecatedNodesEditorValidator` (module **`ConventionKeeperValidationEditor`**, plugin **ConventionKeeperValidation**).

## Purpose

Fail validation when a **StateTree** asset uses **deprecated** graph nodes (conditions, tasks, evaluators, considerations) or their instance-data types, including:

- Reflected deprecation metadata on the node / instance `UScriptStruct`
- `CPF_Deprecated` / `DeprecatedProperty` on properties in those layouts
- `UObject` properties whose class is deprecated (`CLASS_Deprecated` or deprecation metadata)

## Setup

1. Add rule **`StateTree Deprecated Nodes`** (`UConventionKeeperRule_StateTreeDeprecatedNodes`) to your convention asset.
2. Set **`ValidationRoot`** (and optional flags) like any **`UConventionKeeperRule_AssetValidation`** rule.

## See also

- `Docs/Rules/asset-validation.md` — base **AssetValidation** rule and properties.
