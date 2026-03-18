# asset-naming-landscape-layer

Ассеты **Landscape Layer** (Layer Info Object) должны иметь префикс **LL_**.

**Верно:** `LL_Grass`, `LL_Rock`, `LL_Sand_01`  
**Неверно:** `Grass`, `LandscapeLayer_Grass`, `Layer_Grass`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только ассеты типа Landscape Layer Info Object.

## Зачем

В [UE5 Style Guide 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous) для Landscape Layer задан префикс LL_, чтобы такие ассеты было проще находить при рисовании и управлении слоями ландшафта.

## Ссылки

- [UE5 Style Guide – 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
