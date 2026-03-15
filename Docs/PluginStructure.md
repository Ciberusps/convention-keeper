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
         ┌────────────────────┼────────────────────┬────────────────────┐
         ▼                    ▼                      ▼                    ▼
  Rule_AssetNaming    Rule_FolderStructure    Rule_NamingConvention   Rule_* (other bases)
         │                    │                      │
         │  "Concrete" rules = thin subclasses, only set defaults:
         │                    │                      │
         ├── ...              ├── ...                └── Rule_NamingConvention_PascalCase
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
│       ├── ConventionKeeperRule_FolderStructure.h/.cpp
│       ├── ConventionKeeperRule_NamingConvention.h/.cpp
│       └── ConventionKeeperRule_NamingConvention_PascalCase.h/.cpp
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
│   │   ├── folder-structure-content.md
│   │   ├── folder-structure-core-ai.md
│   │   ├── ru/                   ← переводы: та же структура имён
│   │   │   ├── folder-structure-content.md
│   │   │   └── folder-structure-core-ai.md
│   │   └── fr/
│   │       ├── folder-structure-content.md
│   │       └── ...
│   └── RuleOverrideSystem.md
├── Source/
│   └── ConventionKeeperConventions/
│       └── UHLConvention/
│           └── Rules/            ← только код правил, без доков
│               ├── Rule_FolderContent.h/.cpp
│               └── ...
```

## Checklist для новых Rule'ов (кроме BaseRule)

Для **каждого нового конкретного правила** (не для абстрактного `UConventionKeeperRule`):

1. **Документация**
   - `Docs/Rules/{RuleId}.md` — описание правила, примеры, rationale.
   - Ссылки на [UE5 Style Guide (v2)](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file) в разделе **References**, если правило соотносится со стиль-гайдом (указывать конкретный якорь, напр. `#21-folder-names`).
   - `Docs/Rules/ru/{RuleId}.md` — перевод того же текста.

2. **Локализация**
   - В конструкторе правила: `DescriptionKey = FName(TEXT("RuleDesc_{RuleId}"));`
   - `Source/ConventionKeeperEditor/Private/Localization/Strings_en.inl`: запись `{ FName(TEXT("RuleDesc_{RuleId}")), TEXT("...") }` с описанием правила на английском.
   - `Source/ConventionKeeperEditor/Private/Localization/Strings_ru.inl`: то же на русском.
   - Любые новые сообщения валидации (ошибки/предупреждения) — отдельные ключи в обоих .inl.

3. **Путь к доку**
   - По умолчанию используется шаблон из Settings (`DocsRulePathTemplate` = `Docs/Rules/{RuleId}.md`). Если файл лежит там, переопределение не нужно. Иначе задать `DocPathOverride` в правиле.
