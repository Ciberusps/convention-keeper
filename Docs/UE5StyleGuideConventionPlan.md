# План: UE5StyleGuideConvention

Конвенция по [Gamemakin UE5 Style Guide (v2)](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file). Документация большая, делаем по этапам. Этот файл — план этапов и **кандидаты в правила** со ссылками на стиль-гайд; лишнее отмечаем и отсекаем по ходу.

---

## Этапы

| Этап | Содержание |
|------|-------------|
| **1** | Выделить список правил и базовых типов (этот документ). Отметить дубликаты и лишнее. |
| **2** | **Directory structure** — правила на папки (FolderStructure, при необходимости FolderNaming). Реализовать в UE5StyleGuideConvention/Rules/. |
| **3** | **Asset naming** — префиксы/суффиксы по типам ассетов. Либо расширить Rule_AssetNaming (таблица prefix/suffix по классу), либо много тонких правил. Вынести в отдельную подсекцию, решить формат. |
| **4** | **На потом:** Blueprint / Static Mesh / Texture / Map validation — см. раздел «На потом» в конце документа. |

---

## Кандидаты в правила (со ссылками на ue5-style-guide)

Ссылки ведут на ветку v2:  
`https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#<якорь>`

### 00. Globally Enforced Opinions

| Секция | Ссылка | Решение |
|--------|--------|---------|
| 00.1 Forbidden Characters (identifiers) | [#00-globally-enforced-opinions](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#00-globally-enforced-opinions) | **Не делаем.** Движок уже не даёт создавать ассеты со спецсимволами/пробелами/Unicode. Отдельное правило не нужно. |

---

### 1. Asset Naming Conventions

| Секция | Ссылка | Предполагаемый RuleId | Базовое правило | Заметки |
|--------|--------|------------------------|-----------------|---------|
| 1.1 Base Asset Name (Prefix_BaseAssetName_Variant_Suffix) | [#1-asset-naming-conventions](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#1-asset-naming-conventions) | `asset-naming-pattern` | AssetNaming (расширение) | Общий шаблон имени. У нас уже есть NamingTemplate; возможно обобщить под Prefix_Base_Variant_Suffix. |
| 1.2.1 Most Common (BP_, M_, S_, SK_, T_, PS_, WBP_, Level suffixes) | [#anc-common](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#12-asset-name-modifiers) | см. блок «Asset naming rules» ниже | AssetNaming | Много типов; вынесены в отдельный список. |
| 1.2.2 Animations (A_, AO_, ABP_, AM_, BS_, LS_, MT_, Rig_, CR_, SKEL_) | [#anc-animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) | то же | AssetNaming | |
| 1.2.3 AI (AIC_, BT_, BB_, BTDecorator_, BTService_, BTTask_, EQS_) | [#anc-ai](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence) | то же | AssetNaming | |
| 1.2.4 Blueprints (BP_, BPFL_, BPI_, BPML_, E, F/S, TBP_, WBP_) | [#anc-bp](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints) | то же | AssetNaming | |
| 1.2.5 Materials (M_, PP_, MF_, MI_, MPC_, SP_, PM_, _Decal) | [#anc-materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials) | то же | AssetNaming | |
| 1.2.6 Textures (T_, суффиксы _D, _N, _R, _A, _O, TC_, MT_, RT_, RTC_, TLP) | [#anc-textures](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#126-textures) | то же | AssetNaming | |
| 1.2.7 Miscellaneous (VFA_, CA_, Curve_, DT_, FT_, FFE_, LG_, LL_, SS_, VF_, SGI_, SIF_, TI_ и др.) | [#anc-misc](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous) | то же | AssetNaming | |
| 1.2.8 Paper 2D (PFB_, SPR_, SPRG_, TM_, TS_) | [#anc-paper2d](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#128-paper-2d) | то же | AssetNaming | |
| 1.2.9 Physics (PM_, PHYS_, DM_) | [#anc-physics](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#129-physics) | то же | AssetNaming | |
| 1.2.10 Sound (DV_, DW_, MSW_, ATT_, Reverb_, Mix_, A_/_Cue, _SC) | [#anc-sounds](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#1210-sounds) | то же | AssetNaming | |
| 1.2.11 UI (Font_, Brush_, Style_, WBP_) | [#anc-ui](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#1211-user-interface) | то же | AssetNaming | |
| 1.2.12 Effects (PS_, PP_) | [#anc-effects](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#1212-effects) | то же | AssetNaming | |

---

### 2. Content Directory Structure

| Секция | Ссылка | Предполагаемый RuleId | Базовое правило | Заметки |
|--------|--------|------------------------|-----------------|---------|
| 2.1.1 Folder names: PascalCase | [2.1 Folder Names](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#21-folder-names) | **`naming-convention-pascalcase`** | Новый BaseRule (NamingRule) для папок и ассетов | Имена папок и ассетов в PascalCase. Стиль-гайд 2.1 говорит про папки; правило обобщаем и на ассеты. |
| 2.2 Top-level folder for project | [2.2 Top Level Folder](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#22-use-a-top-level-folder-for-project-specific-assets) | `folder-top-level-project` | FolderStructure | Все ассеты под `Content/{ProjectName}/`. |
| 2.3 Developers folder | [2.3 Developer Folders](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#23-use-developers-folder-for-local-testing) | `folder-developers` | FolderStructure | Папка Developers для локальных экспериментов; опционально «должна существовать» или «не использовать в продакшене». |
| 2.4 Maps in Maps folder | [2.4 Maps](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#24-all-map-files-belong-in-a-folder-called-maps) | `folder-maps` | FolderStructure | Все карты в `Content/Project/Maps`. |
| 2.5 Core folder | [2.5 Core](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#25-use-a-core-folder-for-critical-blueprints-and-other-assets) | `folder-core` | FolderStructure | Папка Core для критичных BP и т.д. |
| 2.6 No folders named Assets / Meshes / Textures / Materials | [2.6 Assets and AssetTypes](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#26-do-not-create-folders-called-assets-or-assettypes) | `folder-no-asset-type-names` | **FolderStructure (banned)** или новый тип | Запрет папок с именами типа Assets, Meshes, Textures, Materials. |
| 2.7 Large sets (Animations, Audio) | [2.7 Large Sets](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#27-very-large-asset-sets-get-their-own-folder-layout) | `folder-large-sets` | FolderStructure / информационное | Рекомендация: Animation/Audio в своих подпапках (Characters/Common/Animations и т.д.). Сложнее автоматизировать. |
| 2.8 MaterialLibrary | [2.8 Material Library](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#28-materiallibrary) | `folder-material-library` | FolderStructure | Папка MaterialLibrary с подпапками (Debug, Utility и т.д.). |
| 2.9 No empty folders | [2.9 No Empty Folders](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#29-no-empty-folders) | `no-empty-folders` | **FolderStructure**: расширение флагом `bNoEmptyFolders` (или аналог) | Запрет пустых папок в зоне действия правила. Не отдельный BaseRule — опция в Rule_FolderStructure. |

---

### 5. Niagara

| Секция | Ссылка | Предполагаемый RuleId | Базовое правило | Заметки |
|--------|--------|------------------------|-----------------|---------|
| 5.1 No spaces (Niagara identifiers) | [5.1 Niagara](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#51-no-spaces-ever) | не делаем | — | Для ассетов движок уже не даёт спецсимволы; отдельное правило избыточно. |

---

## Asset naming rules (отдельно)

Их **много**, все простые по смыслу: «в такой папке/типе ассета — такой префикс (и суффикс)». Варианты:

1. **Расширить Rule_AssetNaming**  
   Поддержать конфиг: класс ассета (или путь) → обязательный префикс, опциональный суффикс (и шаблон). Один rule на тип ассета или один общий rule с таблицей из конфига/Convention.

2. **Много тонких правил**  
   Один rule на подсекцию 1.2.x (Most Common, Animations, AI, Blueprints, Materials, Textures, Misc, Paper2D, Physics, Sound, UI, Effects) — каждый знает свой набор классов и префиксов/суффиксов. Плюс: явность. Минус: десятки правил.

3. **Гибрид**  
   Один конфигурируемый AssetNaming с таблицей префиксов/суффиксов по классам (из стиль-гайда), плюс при необходимости 1–2 отдельных rule для особых случаев (например, Level suffixes, Sound Class без префикса).

Рекомендация для обсуждения: **сначала расширить AssetNaming** (таблица prefix/suffix по классу), затем завести в UE5StyleGuideConvention один или несколько rule’ов, заполняющих эту таблицу из ue5-style-guide (1.2.1–1.2.12). Отдельные тонкие rule’ы добавлять только где формат реально отличается (например, Level, Sound Class). Проверку на спецсимволы (00.1) не вводим — движок уже не даёт создавать такие ассеты.

---

## Новые BaseRule’ы (в работу сейчас)

| RuleId | Описание | Базовое правило |
|--------|----------|-----------------|
| **naming-convention-pascalcase** | 2.1: имена папок и ассетов в PascalCase. | Новый BaseRule (NamingRule) для папок и ассетов. |

**no-empty-folders (2.9)** — не отдельный BaseRule. Расширение **FolderStructure**: флаг вроде `bNoEmptyFolders` (или `bDisallowEmptyFolders`): при включении в зоне действия правила запрещать пустые папки.

---

## На потом (Blueprint / Static Mesh / Texture / Map)

Сейчас не делаем. Список для следующих итераций.

### Blueprints (секция 3)

| Секция | Ссылка | RuleId (когда будем делать) | BaseRule |
|--------|--------|------------------------------|----------|
| 3.1 Compiling | [3.1](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#31-compiling) | `blueprint-compile-clean` | BlueprintValidation |
| 3.2 Variables | [3.2](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#32-variables) | `blueprint-variables-naming` и др. | BlueprintValidation |
| 3.3 Functions | [3.3](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#33-functions-events-and-event-dispatchers) | `blueprint-functions-naming` и др. | BlueprintValidation |
| 3.4 Graphs | [3.4](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#34-blueprint-graphs) | `blueprint-graphs-*` | BlueprintValidation |

### Static Meshes (секция 4)

| Секция | Ссылка | RuleId | BaseRule |
|--------|--------|--------|----------|
| 4.1 UVs | [4.1](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#41-static-mesh-uvs) | `static-mesh-uvs` | StaticMeshValidation |
| 4.2 LODs | [4.2](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#42-lods-should-be-set-up-correctly) | `static-mesh-lods` | StaticMeshValidation |
| 4.3 Modular snapping | [4.3](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#43-modular-socketless-assets-should-snap-to-the-grid-cleanly) | `static-mesh-modular-snap` | StaticMeshValidation |
| 4.4 Collision | [4.4](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#44-all-meshes-must-have-collision) | `static-mesh-collision` | StaticMeshValidation |
| 4.5 Scale | [4.5](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#45-all-meshes-should-be-scaled-correctly) | `static-mesh-scale` | StaticMeshValidation |

### Levels / Maps (секция 6)

| Секция | Ссылка | RuleId | BaseRule |
|--------|--------|--------|----------|
| 6.1 No errors/warnings | [6.1](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#61-no-errors-or-warnings) | `map-no-errors` | MapValidation |
| 6.2 Lighting built | [6.2](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#62-lighting-should-be-built) | `map-lighting-built` | MapValidation |
| 6.3 No z-fighting | [6.3](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#63-no-player-visible-z-fighting) | `map-no-zfighting` | MapValidation |
| 6.4 Marketplace | [6.4](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#64-marketplace-specific-rules) | `map-marketplace-overview-demo` | MapValidation |

### Textures (секция 7)

| Секция | Ссылка | RuleId | BaseRule |
|--------|--------|--------|----------|
| 7.1 Power of 2 | [7.1](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#71-dimensions-are-powers-of-2) | `texture-power-of-two` | TextureValidation |
| 7.2 Density | [7.2](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#72-texture-density-should-be-uniform) | `texture-density` | TextureValidation |
| 7.3 Max 8192 | [7.3](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#73-textures-should-be-no-bigger-than-8192) | `texture-max-size` | TextureValidation |
| 7.4 Groups | [7.4](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#74-textures-should-be-grouped-correctly) | `texture-groups` | TextureValidation |

---

## Как пользоваться этим документом

1. Пройтись по таблицам (00, 1, 2, 5) и отметить: **оставляем** / **отложить** / **убрать**.
2. В блоке «Asset naming rules» выбрать подход: расширение AssetNaming vs много тонких правил.
3. В работу сейчас: rule **naming-convention-pascalcase** (имена папок и ассетов в PascalCase); **no-empty-folders** — расширение FolderStructure (`bNoEmptyFolders`). Правило на спецсимволы не делаем — движок уже не даёт создавать ассеты с ними. Всё про Blueprint/StaticMesh/Texture/Map — в разделе «На потом».
4. После этого выносить этапы 2–3 в реализацию в `UE5StyleGuideConvention/Rules/` и в базовые правила в ConventionKeeperEditor.

Ссылка на репозиторий стиль-гайда: [Allar/ue5-style-guide (v2)](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file).
