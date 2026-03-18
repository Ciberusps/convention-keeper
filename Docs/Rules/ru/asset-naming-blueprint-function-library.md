# asset-naming-blueprint-function-library

Ассеты **Blueprint Function Library** должны иметь префикс **BPFL_**.

**Верно:** `BPFL_GameHelpers`, `BPFL_MathUtils`  
**Неверно:** `GameHelpers`, `BP_GameHelpers`, `BFL_Utils`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только Blueprint с родителем BlueprintFunctionLibrary.

## Зачем

В [UE5 Style Guide 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints) для Blueprint Function Library задан префикс BPFL_.

## Ссылки

- [UE5 Style Guide – 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
