# asset-naming-blueprint-component

Ассеты **Blueprint Component** должны иметь префикс **BP_** и суффикс **Component** (например BP_InventoryComponent).

**Верно:** `BP_InventoryComponent`, `BP_HealthComponent`  
**Неверно:** `BP_Inventory`, `InventoryComponent`, `BP_MyComponent_Extra`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только Blueprint с родителем ActorComponent.

## Зачем

В [UE5 Style Guide 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints) для Blueprint Component заданы префикс BP_ и суффикс Component.

## Ссылки

- [UE5 Style Guide – 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
