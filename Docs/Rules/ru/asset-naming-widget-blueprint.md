# asset-naming-widget-blueprint

Ассеты **Widget Blueprint** (UMG) должны иметь префикс **WBP_**.

**Верно:** `WBP_MainMenu`, `WBP_HealthBar`, `WBP_Inventory_Slot`  
**Неверно:** `MainMenu`, `UI_HealthBar`, `Tet_NewWidgetBlueprint`, `NewWidgetBlueprint`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только Widget Blueprint (UMG).

## Зачем

В [UE5 Style Guide 1.2.11 User Interface](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#1211-user-interface) для виджет-блюпринтов задан префикс WBP_; так их легко отличить от обычных Blueprint (BP_).

## Ссылки

- [UE5 Style Guide – 1.2.11 User Interface](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#1211-user-interface)
- [UE5 Style Guide – 1.2.1 Most Common](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#121-most-common) (WBP_ в таблице)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
