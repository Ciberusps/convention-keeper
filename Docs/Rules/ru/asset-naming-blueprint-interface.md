# asset-naming-blueprint-interface

Ассеты **Blueprint Interface** должны иметь префикс **BPI_**.

**Верно:** `BPI_Interactable`, `BPI_Damageable`  
**Неверно:** `Interactable`, `BP_Interactable`, `Interface_Interactable`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только Blueprint с родителем BlueprintInterface.

## Зачем

В [UE5 Style Guide 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints) для Blueprint Interface задан префикс BPI_.

## Ссылки

- [UE5 Style Guide – 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
