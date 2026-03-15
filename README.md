# 🛡️ Convention Keeper (WIP, not ready for production)

**Convention Keeper** - plugin for keeping your conventions, naming, folders, and all other kinds of conventions. Eslint-like system for Unreal Engine.

Support: `all your concerns sweetie 🥰`

## ✨ Features

- Conventions
- Naming conventions
- FolderStructure conventions
- Exclusions
- Localization
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

- ConventionKeeper convention (recommended) - default convention, you can create your own conventions by extending it (inherits from ue5-style-guide convention with overrides/additions)
- [ue5-style-guide](https://github.com/Allar/ue5-style-guide) convention - 1 to 1 implementation of the UE5 Style Guide

## 🌐 Localization & languages

Rule descriptions, validation messages in the Message Log, and the “ConventionKeeper offline” message are localized.

**Supported languages**

| Code | Language |
|------|----------|
| `en` | English (default) |
| `ru` | Russian |

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

## 📖 How to use

- use RMB -> Batch Rename to rename assets/folders/etc.
- use Auto-Fix where possible
- set the excluded directories you want to use
- set the excluded classes you want to use

## ▶️ Commandlet (CI / CLI)

Проверка конвенций из командной строки (например, в CI):

```bash
# Вся валидация (по настройкам Convention в Project Settings)
UnrealEditor.exe YourProject.uproject -run=ConventionKeeperCommandlet

# Только указанные пути (разделитель — ;)
UnrealEditor.exe YourProject.uproject -run=ConventionKeeperCommandlet Paths="Content/GameCode;Content/Shared"
```

## 📖 Documentation

## Features TODO:

- folderstructure rules should have severity warn mostly, except root folder rule, make it warn by default
- take settings/good practices from https://github.com/TheEmidee/UENamingConventionValidation
- BP Rules (vars naming, etc.)


## 🤝 Contributing

Contributions welcome! Feel free to open issues or pull requests.

1. Fork repository
2. Create feature branch (`git checkout -b feature/my-feature`)
3. Commit changes (`git commit -am 'Add feature'`)
4. Push branch (`git push origin feature/my-feature`)
5. Open a Pull Request

---

## 📄 License

This project is licensed under the **MIT License**. See [LICENSE](LICENSE) for details.
