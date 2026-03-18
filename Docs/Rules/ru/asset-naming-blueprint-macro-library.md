# asset-naming-blueprint-macro-library

Ассеты **Blueprint Macro Library** должны иметь префикс **BPML_**. В гайде рекомендуется по возможности не использовать macro libraries.

**Верно:** `BPML_CommonMacros`, `BPML_EditorHelpers`  
**Неверно:** `CommonMacros`, `BP_CommonMacros`, `BML_Macros`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только Blueprint с родителем BlueprintMacroLibrary.

## Зачем

В [UE5 Style Guide 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints) для Blueprint Macro Library задан префикс BPML_. Предпочтительнее function libraries (BPFL_).

## Ссылки

- [UE5 Style Guide – 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
