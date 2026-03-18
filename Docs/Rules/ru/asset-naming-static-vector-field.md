# asset-naming-static-vector-field

Ассеты **Static Vector Field** должны иметь префикс **VF_**.

**Верно:** `VF_Wind`, `VF_Vortex`, `VF_Flow_01`  
**Неверно:** `Wind`, `VectorField_Wind`, `VFA_Wind`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только ассеты типа Static Vector Field.

## Зачем

В [UE5 Style Guide 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous) для Static Vector Field задан префикс VF_, чтобы такие ассеты было проще находить и отличать от Animated Vector Field (VFA_).

## Ссылки

- [UE5 Style Guide – 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
