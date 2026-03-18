# asset-naming-curve-vector

Ассеты **Vector Curve** должны иметь префикс **Curve_** и суффикс **_Vector**.

**Верно:** `Curve_MovementPath_Vector`, `Curve_ColorGradient_Vector`  
**Неверно:** `MovementPath`, `Curve_MovementPath`, `VectorCurve_Path`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только ассеты типа CurveVector.

## Зачем

В [UE5 Style Guide 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous) для vector curve заданы префикс Curve_ и суффикс _Vector, чтобы тип кривой был понятен по имени.

## Ссылки

- [UE5 Style Guide – 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
