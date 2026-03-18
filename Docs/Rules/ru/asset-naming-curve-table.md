# asset-naming-curve-table

Ассеты **Curve Table** должны иметь префикс **Curve_** и суффикс **_Table**.

**Верно:** `Curve_WeaponScaling_Table`, `Curve_Experience_Table`  
**Неверно:** `WeaponScaling`, `Curve_WeaponScaling`, `CurveTable_Exp`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только ассеты типа CurveTable.

## Зачем

В [UE5 Style Guide 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous) для curve table заданы префикс Curve_ и суффикс _Table, чтобы их можно было отличить от одиночных кривых.

## Ссылки

- [UE5 Style Guide – 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
