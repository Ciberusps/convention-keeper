# asset-validation (Base Rule: AssetValidation)

**Engine class:** `UConventionKeeperRule_AssetValidation`  
**Plugin:** optional **`ConventionKeeperValidation`** (nested under the Convention Keeper plugin folder). Enables engine plugins **Data Validation** and **StateTree** via its own `.uplugin`; core **ConventionKeeper** has no engine-plugin dependencies.

## Purpose

Run a **single** [`UEditorValidatorBase`](https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Plugins/DataValidation/UEditorValidatorBase) over assets under a **Content-relative root** (`ValidationRoot`), and report issues in the **Convention Keeper** Message Log (with `RuleId` / doc link like other rules).

This rule does **not** execute the full `UEditorValidatorSubsystem` chain on each asset — only the validator class you assign.

## Properties

| Property | Meaning |
|----------|---------|
| `ValidationRoot` | Content path root, e.g. `Content/{ProjectName}/…`. Supports placeholders like FolderStructure rules; trailing slash optional. |
| `bRecursive` | Include subfolders via Asset Registry. |
| `EditorValidatorClass` | Concrete `UEditorValidatorBase` subclass (C++ or BP validator). |
| `LimitToAssetTypes` | If non-empty, only assets whose loaded object `IsA` one of these types. |
| `bRunClassIsDataValid` | If true, run `UObject::IsDataValid` first; on `Invalid`, skip the editor validator for that asset. |
| `bValidateOnPerAssetSave` | If false, rule is skipped when validation is scoped to per-asset package paths (e.g. narrow on-save batch). |

## StateTree (built-in)

- **Rule:** `UConventionKeeperRule_StateTreeDeprecatedNodes` — presets `EditorValidatorClass` to `UConventionKeeperStateTreeDeprecatedNodesEditorValidator` and limits assets to `UStateTree`.
- **Doc:** `Docs/Rules/state-tree-deprecated-nodes.md`

## See also

- `Docs/Features/asset-validation-engine-integration.md` — scope, memory, full-project vs save.
