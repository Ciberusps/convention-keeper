# Contributing to Convention Keeper

Thank you for considering contributing. This document covers testing, how to add new rules, and what to include (documentation, localization, tests).

## Automated testing

Plugin tests do **not** require real assets on disk. Naming rules are checked against **synthetic** `FAssetData` (asset name + class path).

### Running tests (in editor)

1. Disable Live Coding if it is on (or close the editor before building).
2. Open **Window → Developer Tools → Session Frontend** (or **Automation**).
3. Go to the **Tests** tab and filter by `ConventionKeeper`.
4. Run the test group or individual test you need:
   - **`ConventionKeeper.UE5StyleGuideRules`** — naming checks for all UE5 Style Guide asset naming rules (prefix/suffix) using synthetic `FAssetData`.
   - **`ConventionKeeper.AssetNaming`** — templates, suffixes, paths, scopes.
   - **`ConventionKeeper.Commandlet`** — path normalization for the commandlet.

### API for custom tests

Naming rules support checking a **single asset** without scanning content. Use `EvaluateSingleAssetNaming` so you can test rules without creating real assets:

```cpp
#include "AssetRegistry/AssetData.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"

// Build FAssetData by hand (package path, asset name, class path)
FAssetData Data = FAssetData(
    TEXT("/Game/Test/MyTable"),
    TEXT("/Game/Test/MyTable.MyTable"),
    FTopLevelAssetPath(TEXT("/Script/Engine.DataTable")),
    FAssetDataTagMap(), TArrayView<const int32>(), 0u);

TMap<FString, FString> Placeholders;
bool bValid = false;
FString ExpectedPrefix;
Rule->EvaluateSingleAssetNaming(Data, Placeholders, bValid, &ExpectedPrefix, nullptr);
// e.g. bValid == false, ExpectedPrefix == "DT_" for a DataTable rule
```

This lets you cover all prefix/suffix rules (e.g. DT_, VFA_, CA_, OL_) without creating assets in Content.

### Validating real assets (CLI)

Create a test folder (e.g. `Content/GameCode/ConventionKeeperTest/`), add assets with correct and incorrect names, and run the commandlet on that path. Results appear in the log (and in the Message Log when run from the editor).

---

## Adding or changing rules

When you add or change a rule (especially in a convention like UE5 Style Guide), please follow this checklist.

### 1. Documentation (required)

- Add a rule doc in **English**: `Docs/Rules/{RuleId}.md`.
  - Include: what the rule requires, valid/invalid examples, “Applies to”, rationale, references (e.g. UE5 Style Guide section).
- For other languages (e.g. Russian): add `Docs/Rules/{Lang}/{RuleId}.md` with the same structure.

Rule IDs are kebab-case (e.g. `asset-naming-data-table`, `folder-structure-content`).

### 2. Localization (recommended)

- Add the rule description string in **`Source/ConventionKeeperEditor/Private/Localization/Strings_en.inl`**:
  - Key: `RuleDesc_{rule-id}` (e.g. `RuleDesc_asset-naming-data-table`).
  - Value: short description used in the UI and Message Log.
- If you support another language, add the same key in the corresponding `Strings_{lang}.inl` (e.g. `Strings_ru.inl`).

### 3. Tests (required for convention rules)

- For **asset naming** rules that use a fixed prefix (and optionally suffix), add a test in the convention’s spec so that the rule is covered by automated tests.
- For the **UE5 Style Guide** convention, add (or extend) a case in **`Source/ConventionKeeperTests/Private/UE5StyleGuideRules.spec.cpp`**:
  - Create the rule with `NewObject<UUE5StyleGuideRule_AssetNaming_XXX>(GetTransientPackage())`.
  - Build synthetic `FAssetData` with the appropriate asset class path and name (bad and good examples).
  - Call `Rule->EvaluateSingleAssetNaming(...)` and assert:
    - Bad name → `bOutValid == false` and expected prefix/suffix as needed.
    - Good name → `bOutValid == true`.
- If you introduce a **new convention** (not just a new rule in an existing one), add a spec for that convention and cover its rules in the same way (synthetic `FAssetData` + `EvaluateSingleAssetNaming` where applicable).

This keeps convention behaviour regression‑safe and documents expected naming.

### 4. Registration

- Register the new rule in the convention’s constructor (e.g. in `UE5StyleGuideConvention.cpp`):
  - `#include` the rule header.
  - `Rules.Add(CreateDefaultSubobject<UUE5StyleGuideRule_AssetNaming_XXX>(TEXT("Rule_AssetNaming_XXX")));`

---

## Summary checklist for a new naming rule

- [ ] Rule class and implementation (prefix/suffix/class path, etc.).
- [ ] Rule registered in the convention (e.g. `UE5StyleGuideConvention.cpp`).
- [ ] **Documentation**: `Docs/Rules/{RuleId}.md` (and optional `Docs/Rules/{Lang}/{RuleId}.md`).
- [ ] **Localization**: `RuleDesc_{rule-id}` in `Strings_en.inl` (and optional `Strings_{lang}.inl`).
- [ ] **Test**: at least one `It(...)` in the convention’s spec (e.g. `UE5StyleGuideRules.spec.cpp`) using synthetic `FAssetData` and `EvaluateSingleAssetNaming`.

If you are unsure which spec file or convention to extend, open an issue or check existing rules of the same type (e.g. other `UE5StyleGuideRule_AssetNaming_*` rules and their tests).
