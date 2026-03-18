# asset-naming-data-table

Ассеты **Data Table** должны иметь префикс **DT_**.

**Верно:** `DT_WeaponStats`, `DT_CharacterData`, `DT_LootTable_01`  
**Неверно:** `WeaponStats`, `DataTable_Items`, `MyTable`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только ассеты типа DataTable.

## Зачем

В [UE5 Style Guide 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous) для Data Table задан префикс DT_, чтобы ассеты было проще находить и фильтровать.

## Ссылки

- [UE5 Style Guide – 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
