# 🛡️ Convention Keeper (WIP, not ready for production, ETA early april)

**Convention Keeper** - plugin for keeping your conventions - naming, folders structure, etc. and all other kinds of conventions. Eslint-like system for Unreal Engine.

Conventions allow us to make games faster not wasting time on communication to enforce rules in our teams, helps us to keep the project consistent, not wasting time on cleaning up the project(how many times we were doing this) and helping new developers to understand the project rules faster without constantly whining/bulling them 🤣 and wasting time on review.

Support: `all your concerns sweetie 🥰`

## ✨ Features

- Conventions
- Rules for assets naming, folder structure
- Exclusions
- Localization
- **Convention Coverage & Compliance** — two metrics: *in rule scope* (share of assets in a path where a rule applies) and *compliance* (of those in scope, how many pass). Run from **Tools → Convention Coverage** or **Convention Compliance**, or **Project Settings → Convention Keeper**
- TODO: Auto-fix
- and all kinds of shitty conventions

## 🚀 Install & ⬆️ Update

```bash
// install as git submodule to your plugins folder
git submodule add https://github.com/Ciberusps/convention-keeper.git ./Plugins/convention-keeper

// to update plugin
git submodule update --remote`
```

## 🚀 Setup

TODO how to setup in project

- open Project Settings
- set project name folder - your main folder name in Content/ (defaults to the project name)
- language override for the project (Project Settings)
- language override for the user (Editor Settings)
- go to Convention Keeper
- set the convention you want to use
- set the rules you want to use

## 🛡️ Conventions already implemented

- [ue5-style-guide](https://github.com/Allar/ue5-style-guide) convention - 1 to 1 implementation of the UE5 Style Guide
- Earendil Convention (recommended) — default Convention Keeper convention (`UEarendilConvention`), more UE5 asset coverage than ue5-style-guide alone. Extend it or create your own (inherits from UE5 Style Guide convention with overrides/additions).


## 🌐 Localization & languages

Rule descriptions, validation messages in the Message Log, and the “ConventionKeeper offline” message are localized.

**Supported languages**

| Code | Language |
|------|----------|
| `en` | English (default) |
| `ru` | Russian |
| more | to come |

**Where to set**

- **Project (default):** Project Settings → Convention Keeper → **Default Language**
  - *Auto (system)* — use editor/system language; *English* / *Russian* — force that language.
- **Per user:** Project Settings → **Convention Keeper (Local)** → **Local Override Language**
  - Stored in `Saved/Config/` (not in project). *Use project default* / *English* / *Russian*.

**Rule docs**

- English: `Docs/Rules/{RuleId}.md`
- Other languages: `Docs/Rules/{Lang}/{RuleId}.md` (e.g. `Docs/Rules/ru/folder-structure-content.md`).
- If a localized file exists, the clickable rule link in the Message Log opens that version; otherwise the English doc is used.

## 🤔 How it works

- Conventions - are sets of rules that are used to validate the structure of the project
- Rules - are used to validate project assets/folders/etc.
- Every rule has description, localization, documentation, severity and so on

### Your own convention: base rules only vs subclassing

- **Light path (recommended to start):** create a **Convention** asset (or duplicate a preset) and add **base rule types** from the editor directly — *Folder Structure*, *Asset Naming*, *Asset Placement*, *Naming Convention (PascalCase)*, etc. Configure paths, templates, and severities in the details panel. No C++ or Blueprint subclasses required; you get validation immediately. Docs links use **RuleId** + `Docs/Rules/{RuleId}.md` when you set them; empty **RuleId** just skips the doc URL — still fine for internal use.

- **Full path:** subclass a base rule in **C++** or **Blueprint** when you need a stable **RuleId**, shared markdown, overrides in **RuleOverrides**, or custom **Validate** logic. That’s the route for teams that want everything aligned with repo docs and CONTRIBUTING-style workflow.

Preset conventions (Earendil, UE5 Style Guide) are built from the same base types; you can mirror that **only with editor-placed base rules**, or extend presets via **Extends Convention** and tweak the **Rules** array.

## Convention Coverage & Compliance

Two separate checks:

- **In rule scope** — share of assets that lie in a path where a rule applies (e.g. under `Content/{ProjectName}/...`). So e.g. "23% in scope" for AnimSequence means 23% of all AnimSequence assets are in such paths; the rest are outside any rule’s path. Use this to see *which types need rules* (0% in scope = no rule path matches).
- **Compliance** — of assets *in scope*, how many *pass* the rule (naming/placement). So "0% compliant (0/283)" means 283 are in scope but none pass; fix names/paths to raise compliance.

**How to run:** **Tools → Convention Coverage** (coverage only) or **Convention Compliance** (compliance only), or **Project Settings → Convention Keeper** → **Run coverage report** / **Run compliance report**.

## 📖 How to use

- use RMB -> Batch Rename to rename assets/folders/etc.
- use Auto-Fix where possible
- set the excluded directories you want to use
- set the excluded classes you want to use

## ▶️ Commandlet (CI / CLI)

Run from the command line (e.g. in CI):

**Validation (folder structure + asset naming/placement for given paths):**

```bash
# Full validation (uses Convention from Project Settings)
UnrealEditor.exe YourProject.uproject -run=ConventionKeeperCommandlet

# Only specified paths (separator: ;)
UnrealEditor.exe YourProject.uproject -run=ConventionKeeperCommandlet Paths="Content/GameCode;Content/Shared"

# Validate specific assets (package paths without .uasset). Without -AssetPaths, paths are treated as folders.
UnrealEditor.exe YourProject.uproject -run=ConventionKeeperCommandlet Paths="Content/GameCode/Maps/Main" -AssetPaths
```

**Rule coverage & compliance (no validation, only report; useful for CI):**

```bash
# Print rule coverage and compliance to log; exit 0
UnrealEditor.exe YourProject.uproject -run=ConventionKeeperCommandlet -Coverage -Compliance

# Compliance gate: exit 1 if compliance % is below threshold (from settings or -MinCompliance=N)
UnrealEditor.exe YourProject.uproject -run=ConventionKeeperCommandlet -Compliance -MinCompliance=90

# Coverage gate: exit 1 if rule coverage % is below threshold
UnrealEditor.exe YourProject.uproject -run=ConventionKeeperCommandlet -Coverage -MinCoverage=80
```

- **-Coverage** — print rule coverage. With **-MinCoverage=N** or **Min coverage % (CI)** in Project Settings, exit 1 if coverage is below N%.
- **-Compliance** — print compliance. With **-MinCompliance=N** or **Min compliance % (CI)** in Project Settings, exit 1 if compliance is below N%.

For details on automated testing and adding new rules, see [CONTRIBUTING.md](CONTRIBUTING.md).

## 📖 Documentation

## Features TODO:

- folderstructure rules should have severity warn mostly, except root folder rule, make it warn by default
- take settings/good practices from https://github.com/TheEmidee/UENamingConventionValidation
- BP Rules (vars naming, etc.)


## 🤝 Contributing

Contributions are welcome. Please read [CONTRIBUTING.md](CONTRIBUTING.md) for testing expectations, how to add new rules (documentation, localization, tests), and workflow.

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/my-feature`)
3. Commit your changes (`git commit -am 'Add feature'`)
4. Push the branch (`git push origin feature/my-feature`)
5. Open a Pull Request

---

## 📄 License

This project is licensed under the **MIT License**. See [LICENSE](LICENSE) for details.
