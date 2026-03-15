# asset-naming-physical-material

Ассеты **Physical Material** должны иметь префикс **PM_**.

**Верно:** `PM_Metal_Steel`, `PM_Concrete`, `PM_Glass`, `PM_Wood_01`  
**Неверно:** `M_Metal`, `PhysicalMaterial_Steel`, `PhysMat_Glass`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только Physical Material.

## Зачем

В [UE5 Style Guide 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials) для physical materials задан префикс PM_; так их легко отличить от рендер-материалов (M_, MI_).

## Ссылки

- [UE5 Style Guide – 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
