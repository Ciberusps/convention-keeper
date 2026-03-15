# Система Override правил (ESLint-подобная)

## Цель

- Пользователь может **наследоваться** от конвенции (например UHLConvention) и **переопределять** только нужные правила (отключить или заменить).
- При выходе патча в UHL с **новым правилом** оно автоматически появляется у всех, кто от него наследуется, без ручного копирования `Rules`.

## Текущее состояние

### ConventionKeeper

- **UConventionKeeperConvention**: база, хранит `TArray<TObjectPtr<UConventionKeeperRule>> Rules`.
- **UUHLConvention**: в конструкторе заполняет `Rules` через `CreateDefaultSubobject` (Rule_Content, Rule_ProjectName, Rule_Character, Rule_CoreAI).
- **Settings**: `TSubclassOf<UConventionKeeperConvention> Convention` (по умолчанию UUHLConvention); везде используется `Convention.GetDefaultObject()`.

**Проблема**: при наследовании (C++ или Blueprint) дочерний класс/ассет имеет **свою копию** `Rules`. У Blueprint она сериализуется в ассет — при добавлении нового правила в UHL конвенция пользователя по-прежнему видит только старый набор. У C++-наследника пришлось бы дублировать весь конструктор UHL и потом добавлять свои правила — хрупко и не масштабируется.

### UENamingConventionValidation

- Конфигурация через **DeveloperSettings**: `ClassDescriptions`, `ExcludedDirectories`, `ExcludedClasses`, `BlueprintsPrefix`.
- Валидаторы: **автопоиск** — `GetDerivedClasses(UEditorNamingValidatorBase)` и Blueprint-валидаторы (EditorUtilityBlueprint, наследующие `UEditorNamingValidatorBase`).
- Модели extend/override **нет**: всё аддитивно (добавляешь классы в список, добавляешь валидаторы). Новые правила = новые валидаторы в коде/Blueprint.

Для ConventionKeeper нужна именно модель **«расширить конфиг + переопределить по id»**, как в ESLint.

---

## Модель ESLint (кратко)

- **extends**: массив конфигов; дочерний конфиг мержит с базовым.
- **rules**: объект `ruleId -> "off" | "warn" | "error" | [severity, options]`.
- Итоговый набор правил = правила из extended-конфигов + локальные переопределения по `ruleId`. Новое правило в базе автоматически попадает в дочерний конфиг с дефолтной severity, если пользователь его не переопределил.

---

## Варианты реализации в Unreal

### Вариант 1: ExtendsConvention + RuleOverrides (рекомендуемый)

**Идея**: конвенция может указывать **расширяемую конвенцию** (ESLint-style `extends`) и список **переопределений по стабильному RuleId**. Эффективный список правил **вычисляется** в рантайме, а не хранится целиком в дочерней конвенции.

**Изменения в типах**

1. **UConventionKeeperRule** (базовый класс правил):
   - **Стабильный идентификатор**: `UPROPERTY(EditDefaultsOnly) FName RuleId;`  
   - В UHL для правил FolderStructure задавать id с префиксом и через тире, например: `folder-structure-content`, `folder-structure-project-name`, `folder-structure-character`, `folder-structure-core-ai`.

2. **UConventionKeeperConvention**:
   - `UPROPERTY(EditAnywhere) TSubclassOf<UConventionKeeperConvention> ExtendsConvention;` — опционально, если не задан — это «корневая» конвенция.
   - `UPROPERTY(EditAnywhere) TArray<FRuleOverride> RuleOverrides;`  
   - `UPROPERTY(EditAnywhere) TArray<TObjectPtr<UConventionKeeperRule>> AdditionalRules;` — правила без RuleId из базы (только свои).

3. **Структура переопределения** (Blueprint-friendly):

```cpp
USTRUCT(BlueprintType)
struct FRuleOverride
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere) FName RuleId;
    UPROPERTY(EditAnywhere) bool bEnabled = true;
    UPROPERTY(EditAnywhere, meta = (EditCondition = "!bEnabled")) TObjectPtr<UConventionKeeperRule> ReplacementRule;
};
```

Либо вместо `bool bEnabled` — enum: `UseBase | Off | Replace`, и при `Replace` — подставлять `ReplacementRule`.

4. **Вычисление эффективных правил**:
   - `GetEffectiveRules()` (виртуальная или финальная):
     - Если `ExtendsConvention` не задан → возвращаем `Rules` (как сейчас у UHL).
     - Иначе: `BaseRules = ExtendsConvention.GetDefaultObject()->GetEffectiveRules()`.
     - По каждому правилу из `BaseRules`: если у правила есть `RuleId` и в `RuleOverrides` есть запись с таким id — при `Off` пропускаем, при `Replace` подставляем `ReplacementRule`.
     - В конец добавляем `AdditionalRules`.
   - Везде, где сейчас используется `Rules`, использовать `GetEffectiveRules()`.

**Плюсы**: новые правила в UHL автоматически попадают ко всем наследникам; переопределять можно только нужные; поддержка Blueprint через `ExtendsConvention` + массив `RuleOverrides` + опционально свои правила в `AdditionalRules`.  
**Минусы**: нужно ввести RuleId и один проход мержа (простая логика).

---

### Вариант 2: Конвенция как Data Asset (база — ассет)

**Идея**: конвенция — не класс с CDO, а **экземпляр** (UDataAsset или отдельный UConventionKeeperConvention-подтип, сохраняемый как ассет). У пользователя ассет «MyProjectConvention», в нём поле **Base Convention** указывает на ассет (например, плагинный «UHLConvention»). Эффективные правила = правила из базового ассета + overrides + свои.

- Патч плагина обновляет **базовый ассет** (например `/ConventionKeeper/Defaults/UHLConvention`). Все конвенции, ссылающиеся на него, при следующем вызове `GetEffectiveRules()` получают новый набор из базы.
- Override по RuleId — так же, как в варианте 1: в дочернем ассете храним `RuleOverrides` и `AdditionalRules`.

**Плюсы**: явный «документ» конфигурации, обновление базы через контент.  
**Минусы**: смена модели с «класс в настройках» на «ассет в настройках»; нужно решить, остаётся ли в Settings `TSubclassOf` или `TSoftObjectPtr<UConventionKeeperConvention>` на ассет; для Blueprint-наследования от UHL по-прежнему лучше вариант 1 (Blueprint может наследовать класс и задать BaseConvention = UUHLConvention).

---

### Вариант 3: Два массива — Inherited (read-only) + Custom

**Идея**: в конвенции **не хранить** полную копию `Rules`, а хранить только:
- `ExtendsConvention` (опционально),
- `RuleOverrides` (по RuleId: off / replace),
- `CustomRules` — только «свои» правила.

Эффективные правила = `GetInheritedRules()` (рекурсивно от базы) + применение overrides + `CustomRules`. По сути это та же семантика, что вариант 1, но с явным разделением «наследованные» (не редактируемые в дочерней конвенции) и «кастомные». Реализационно это может быть тот же `GetEffectiveRules()`, просто в дочерней конвенции массив `Rules` не используется для хранения наследованных — только `AdditionalRules`/`CustomRules`.

---

## Рекомендация

**Вариант 1 (ExtendsConvention + RuleOverrides + GetEffectiveRules())** даёт нужное поведение в духе ESLint, минимально меняет текущую модель (остаётся `TSubclassOf` в Settings, конвенция по-прежнему класс с опциональным `extends`) и хорошо дружит с Blueprint:

- В редакторе пользователь выбирает свой Blueprint конвенции (наследник UHLConvention).
- В Blueprint задаёт `ExtendsConvention = UUHLConvention` (или оставляет родительский класс и тогда extends = родитель).
- В `RuleOverrides` отключает или заменяет правила по `RuleId` (например `folder-structure-character`, `folder-structure-core-ai`).
- При необходимости добавляет свои правила в `AdditionalRules` (для них RuleId может быть пустым или игнорироваться при мерже).

При добавлении нового правила в UHL (новый `RuleId`, новый элемент в `Rules`) все конвенции, у которых ExtendsConvention = UHL, автоматически получают это правило через `GetEffectiveRules()`.

---

## Поддержка Blueprint

- `UConventionKeeperConvention` уже `Blueprintable`, `EditInlineNew`.
- `FRuleOverride`: `BlueprintType`, все поля `EditAnywhere` — редактируется в Details.
- `ExtendsConvention`: `TSubclassOf` — в Blueprint выбирается класс (в т.ч. родительский или UUHLConvention).
- `GetEffectiveRules()` — вызывать из C++ (commandlet, кнопка валидации); в Blueprint при необходимости можно экспортировать как BlueprintCallable.
- Правила с `RuleId` в базе задаются в C++ (UHL); в Blueprint пользователь только включает/выключает/заменяет по id и добавляет свои в `AdditionalRules`.

---

## Краткий чеклист внедрения (вариант 1)

1. В `UConventionKeeperRule` поле `FName RuleId`; в UHL для FolderStructure правил — id с префиксом и тире: `folder-structure-content`, `folder-structure-project-name`, `folder-structure-character`, `folder-structure-core-ai`.
2. Ввести `FRuleOverride` и поля `ExtendsConvention`, `RuleOverrides`, `AdditionalRules` в `UConventionKeeperConvention`.
3. Реализовать `GetEffectiveRules()` с мержем от базы и применением overrides.
4. Заменить использование `Rules` на `GetEffectiveRules()` в валидации (ValidateFolderStructures, ValidateFolderStructuresForPaths и т.д.).
5. У UHL оставить заполнение только `Rules` (без ExtendsConvention); у пользовательских конвенций задавать `ExtendsConvention = UUHLConvention` и при необходимости заполнять `RuleOverrides` и `AdditionalRules`.
