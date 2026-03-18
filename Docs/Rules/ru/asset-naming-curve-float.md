# asset-naming-curve-float

Ассеты **Float Curve** должны иметь префикс **Curve_** и суффикс **_Float**.

**Верно:** `Curve_DamageOverTime_Float`, `Curve_HealthRegen_Float`  
**Неверно:** `DamageOverTime`, `Curve_HealthRegen`, `FloatCurve_Health`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только ассеты типа CurveFloat.

## Зачем

В [UE5 Style Guide 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous) для float curve заданы префикс Curve_ и суффикс _Float, чтобы тип кривой был понятен по имени.

## Ссылки

- [UE5 Style Guide – 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
