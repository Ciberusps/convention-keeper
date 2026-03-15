# Структура плагина (target)

## Modules

Отдельный модуль под готовые конвенции (UHL, UE5 Style Guide и т.д.), чтобы не засорять ядро. Зависит от текущего модуля.

```
Plugins/convention-keeper/
├── ConventionKeeperEditor        ← текущий модуль (базы Convention/Rule, UI, валидация, Settings)
│   ├── Convention, Rule, Rule_AssetNaming, Rule_FolderStructure
│   ├── AssetTypeActions, Factories, Style, Commands
│   └── ...
│
├── ConventionKeeperConventions   ← NEW: пресеты конвенций + их правила (depends on ConventionKeeperEditor)
│   ├── UHLConvention/
│   │   ├── UHLConvention.h/.cpp
│   │   └── Rules/                    ← правила, специфичные для UHL
│   ├── UE5StyleGuideConvention/
│   │   ├── UE5StyleGuideConvention.h/.cpp
│   │   └── Rules/
│   └── ...
│
└── ConventionKeeperTests         ← depends on ConventionKeeperEditor (и при необходимости ConventionKeeperConventions)
```

- **ConventionKeeperEditor** — как сейчас: базовые типы, правила, редакторский функционал.
- **ConventionKeeperConventions** — только классы конвенций и их правила; подключаешь модуль — получаешь UHL/UE5StyleGuide в пикере, не подключаешь — в проекте только свои конвенции.

## Rule classes: few bases, thin subclasses

In UI the user sees **only base rule types** (no clutter). Concrete rules = thin subclasses (often header-only) or data in Convention.

```
                    UConventionKeeperRule (abstract)
                              │
         ┌────────────────────┼────────────────────┐
         ▼                    ▼                    ▼
  Rule_AssetNaming    Rule_FolderStructure    Rule_* (other bases)
         │                    │
         │  "Concrete" rules = thin subclasses, only set defaults:
         │
         ├── Rule_AssetNaming_CharacterAnimations   (.h only: RuleId, severity, description)
         ├── Rule_AssetNaming_Textures
         ├── Rule_FolderStructure_Content
         └── Rule_FolderStructure_CoreAI
```

- **Class picker / "New rule"**: only `Rule_AssetNaming`, `Rule_FolderStructure`, … (3–5 base classes).
- **Your custom rule**: subclass one base in your game module, set `RuleId` and options in constructor/defaults; no extra .cpp if logic is in the base.

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
│       └── ConventionKeeperRule_FolderStructure.h/.cpp
│
├── ConventionKeeperConventions/        ← пресеты + их rules в одной папке на конвенцию
│   ├── UHLConvention/
│   │   ├── UHLConvention.h/.cpp
│   │   └── Rules/
│   └── UE5StyleGuideConvention/
│       ├── UE5StyleGuideConvention.h/.cpp
│       └── Rules/
│
YourGame/Source/YourGame/
└── Rules/                             ← опционально: свои тонкие правила
    └── Rule_AssetNaming_Characters.h
```

## Документация правил: root Docs/Rules vs рядом с правилом

| | **Root Docs/Rules** (как ESLint) | **Colocated** (UHLConvention/Rules/FooRule/ + .md) |
|---|---|---|
| Путь | `Docs/Rules/{RuleId}.md` в корне плагина | рядом с кодом правила: `.../Rules/FooRule/README.md` или `FooRule.md` |
| Плюсы | Один шаблон URL, уже заложен в Settings (`DocsRulePathTemplate`). Один каталог — проще собирать сайт доков, линковать между правилами. RuleId = имя файла. | Всё по правилу в одной папке: код + док. Перенос/удаление правила = одна папка. |
| Минусы | Код и док в разных местах. | Шаблон пути усложняется (нужен контекст конвенции или полный путь к правилу), либо дублирование RuleId в путях. |

**Рекомендация: root `Docs/Rules/`** — как в ESLint. Один шаблон `Docs/Rules/{RuleId}.md`, без привязки к конвенции; плагин уже под это заточен. Если один и тот же RuleId переиспользуется в разных конвенциях — один общий док. Если позже понадобится «свой» док на конвенцию — можно завести `Docs/Conventions/UHLConvention/Rules/{RuleId}.md` и отдельный шаблон.

**Локализация:** оригиналы в `Docs/Rules/` (плоский список), переводы — в подпапках по языку: `Docs/Rules/ru/`, `Docs/Rules/fr/` и т.д., внутри та же структура имён. Один язык = одна папка, удобно отдавать переводчикам и масштабировать. Порядок выбора: `Docs/Rules/{lang}/{RuleId}.md` → `Docs/Rules/{RuleId}.md` (оригинал).

```
Plugins/convention-keeper/
├── Docs/
│   ├── Rules/                    ← оригиналы (дефолтный язык)
│   │   ├── folder-content.md
│   │   ├── folder-core-ai.md
│   │   ├── ru/                   ← переводы: та же структура имён
│   │   │   ├── folder-content.md
│   │   │   └── folder-core-ai.md
│   │   └── fr/
│   │       ├── folder-content.md
│   │       └── ...
│   └── RuleOverrideSystem.md
├── Source/
│   └── ConventionKeeperConventions/
│       └── UHLConvention/
│           └── Rules/            ← только код правил, без доков
│               ├── Rule_FolderContent.h/.cpp
│               └── ...
```
