# 🛡️ Convention Keeper

**Convention Keeper** - plugin for keeping your conventions, naming, folders, and all other kinds of conventions. Eslint-like system for Unreal Engine.

Support: `all`

## ✨ Features

- Conventions
- Naming conventions
- FolderStructure conventions
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

## 🤔 How it works

- Conventions - are sets of rules that are used to validate the structure of the project
- Rules - are used to validate project assets/folders/etc.

## ▶️ Commandlet (CI / CLI)

Проверка конвенций из командной строки (например, в CI):

```bash
# Вся валидация (по настройкам Convention в Project Settings)
UnrealEditor.exe YourProject.uproject -run=ConventionKeeperCommandlet

# Только указанные пути (разделитель — ;)
UnrealEditor.exe YourProject.uproject -run=ConventionKeeperCommandlet Paths="Content/GameCode;Content/Shared"
```

Код выхода: `0` — успех, `1` — ошибка.

## 📖 Documentation


## TODO:

- GameplayTags Rule
- [ue5-style-guide](https://github.com/Allar/ue5-style-guide)
- localization
- auto-fix


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
