# Plugin structure (target)

## Modules

A separate module for shipped conventions (Earendil, UE5 Style Guide, etc.) so the core stays lean. It depends on the editor module.

```
Plugins/convention-keeper/
├── ConventionKeeperEditor        ← core module (Convention/Rule bases, UI, validation, Settings)
│   ├── Convention, Rule, Rule_AssetNaming, Rule_FolderStructure
│   ├── AssetTypeActions, Factories, Style, Commands
│   └── ...
│
├── ConventionKeeperConventions   ← convention presets + their rules (depends on ConventionKeeperEditor)
│   ├── EarendilConvention/
│   │   ├── EarendilConvention.h/.cpp
│   │   └── Rules/                    ← Earendil preset rules
│   ├── UE5StyleGuideConvention/
│   │   ├── UE5StyleGuideConvention.h/.cpp
│   │   └── Rules/
│   └── ...
│
└── ConventionKeeperTests         ← depends on ConventionKeeperEditor (and ConventionKeeperConventions if needed)
```

- **ConventionKeeperEditor** — base types, rules, editor-facing features.
- **ConventionKeeperConventions** — convention classes and their rules only; enable the module to get Earendil / UE5 Style Guide in pickers; without it you rely on your own conventions.

## Rule classes: few bases, thin subclasses

In the UI the user sees **only base rule types** (no clutter). Concrete rules = thin subclasses (often header-only) or data on the Convention asset.

```
                    UConventionKeeperRule (abstract)
                              │
         ┌────────────────────┼────────────────────┬────────────────────┐
         ▼                    ▼                      ▼                    ▼
  Rule_AssetNaming    Rule_FolderStructure    Rule_NamingConvention   Rule_* (other bases)
         │                    │                      │
         │  "Concrete" rules = thin subclasses, only set defaults:
         │                    │                      │
         ├── ...              ├── ...                └── Rule_NamingConvention_PascalCase
```

- **Class picker / "New rule"**: only `Rule_AssetNaming`, `Rule_FolderStructure`, … (3–5 base classes).
- **Light custom convention:** a **Convention** asset plus **instances of base rule types** (same as in the picker) is enough. **No** C++/Blueprint subclass required — configure each rule in the details panel and save. Good for a quick internal preset without a dedicated `RuleId` / repo `.md` (or set `RuleId` when you want the doc link).
- **Custom rule type (full path):** subclass a base in **C++** (game module) or **Blueprint** with a parent from the editor (`Convention Keeper Rule`, `Folder Structure`, `Asset Naming`, `Naming Convention`, …). Use when you need a stable **RuleId**, repo markdown, custom **Validate** logic, or thin preset-style rules like in `ConventionKeeperConventions`. Class Defaults: `RuleId` and options; in BP: **Event Validate** / **Can Validate**; **Log Rule Validation Message** and **Normalize Relative Path** from the base. Thin C++ preset rules use plain `UCLASS()`; **Blueprintable** is on the **bases** in `ConventionKeeperEditor`.

## Where Conventions and Rules live

```
Content/GameCode/
├── Conventions/
│   └── MyProjectConvention.uasset     ← Convention asset (references rules)
│
Plugins/convention-keeper/Source/
├── ConventionKeeperEditor/
│   └── Rules/
│       ├── ConventionKeeperRule.h
│       ├── ConventionKeeperRule_AssetNaming.h/.cpp
│       ├── ConventionKeeperRule_FolderStructure.h/.cpp
│       ├── ConventionKeeperRule_NamingConvention.h/.cpp
│       └── ConventionKeeperRule_NamingConvention_PascalCase.h/.cpp
│
├── ConventionKeeperConventions/        ← presets + their rules, one folder per convention
│   ├── EarendilConvention/             ← `UEarendilConvention` (default preset) + rules
│   │   ├── EarendilConvention.h/.cpp
│   │   └── Rules/
│   └── UE5StyleGuideConvention/
│       ├── UE5StyleGuideConvention.h/.cpp
│       └── Rules/
│
YourGame/Source/YourGame/
└── Rules/                             ← optional: your own thin rules
    └── Rule_AssetNaming_Characters.h
```

## Rule docs: root `Docs/Rules` vs colocated

| | **Root Docs/Rules** (ESLint-style) | **Colocated** (EarendilConvention/Rules/FooRule/ + .md) |
|---|---|---|
| Path | `Docs/Rules/{RuleId}.md` at plugin root | Next to rule code: `.../Rules/FooRule/README.md` or `FooRule.md` |
| Pros | Single URL template wired in Settings (`DocsRulePathTemplate`). One tree — easier for doc sites and cross-links. RuleId = file name. | Code + doc in one place; moving/removing a rule = one folder. |
| Cons | Code and doc live apart. | Path templates get harder (convention context or full path), or duplicate RuleId in paths. |

**Recommendation: root `Docs/Rules/`** — ESLint-style. One pattern `Docs/Rules/{RuleId}.md`, convention-agnostic; the plugin is built around that. If the same RuleId is reused across conventions, share one doc.

**Conventions:** full preset description, rule lists, and references in `Docs/Conventions/{ConventionDocId}.md`. `{ConventionDocId}` = **OverrideDocumentationId** (Advanced), else a slug from **Name** (lowercase, spaces/`_` → `-`). Translations: `Docs/Conventions/ru/...`. Markdown is **not** inlined in details; use **Documentation URL** and **Open documentation**. **Doc path override** (Advanced) for a custom repo path.

**Localization:** originals in `Docs/Rules/` (flat list); translations in per-language subfolders: `Docs/Rules/ru/`, `Docs/Rules/fr/`, etc., same file names inside. One language = one folder — easy for translators. Resolution order: `Docs/Rules/{lang}/{RuleId}.md` → `Docs/Rules/{RuleId}.md` (fallback).

```
Plugins/convention-keeper/
├── Docs/
│   ├── Rules/                    ← originals (default language)
│   │   ├── folder-structure-content.md
│   │   ├── folder-structure-core-ai.md
│   │   ├── ru/                   ← translations: same file names
│   │   │   ├── folder-structure-content.md
│   │   │   └── folder-structure-core-ai.md
│   │   └── fr/
│   │       ├── folder-structure-content.md
│   │       └── ...
│   ├── Conventions/              ← markdown: file name = Name slug or OverrideDocumentationId
│   │   ├── ue5-style-guide-convention.md
│   │   ├── earendil-convention.md
│   │   └── ru/
│   └── RuleOverrideSystem.md
├── Source/
│   └── ConventionKeeperConventions/
│       └── EarendilConvention/
│           └── Rules/            ← rule code only, no docs here
│               ├── Rule_FolderContent.h/.cpp
│               └── ...
```

## Checklist for new concrete rules (not base `UConventionKeeperRule`)

For **each new concrete rule** (not the abstract `UConventionKeeperRule`):

1. **Documentation**
   - `Docs/Rules/{RuleId}.md` — rule description, examples, rationale.
   - Link [UE5 Style Guide (v2)](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file) under **References** when applicable (use a concrete anchor, e.g. `#21-folder-names`).
   - `Docs/Rules/ru/{RuleId}.md` — Russian translation of the same text.

2. **Localization**
   - In the rule constructor: `DescriptionKey = FName(TEXT("RuleDesc_{RuleId}"));`
   - `Source/ConventionKeeperEditor/Private/Localization/Strings_en.inl`: `{ FName(TEXT("RuleDesc_{RuleId}")), TEXT("...") }` with the English description.
   - `Source/ConventionKeeperEditor/Private/Localization/Strings_ru.inl`: same entry in Russian.
   - Any new validation messages (errors/warnings) — new keys in both `.inl` files.

3. **Doc path**
   - By default Settings use `DocsRulePathTemplate` = `Docs/Rules/{RuleId}.md`. If the file lives there, no override. Otherwise set `DocPathOverride` on the rule.
