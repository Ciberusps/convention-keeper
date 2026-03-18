# asset-naming-curve-color

Ассеты **Color Curve** должны иметь префикс **Curve_** и суффикс **_Color**.

**Верно:** `Curve_UIHighlight_Color`, `Curve_AmbientTint_Color`  
**Неверно:** `UIHighlight`, `Curve_UIHighlight`, `ColorCurve_Ambient`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только ассеты типа CurveLinearColor.

## Зачем

В [UE5 Style Guide 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous) для color curve заданы префикс Curve_ и суффикс _Color, чтобы тип кривой был понятен по имени.

## Ссылки

- [UE5 Style Guide – 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
