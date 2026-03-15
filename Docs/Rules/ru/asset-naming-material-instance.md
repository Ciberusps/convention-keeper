# asset-naming-material-instance

Ассеты **Material Instance** должны иметь префикс **MI_**.

**Верно:** `MI_Rock_Snow`, `MI_Character_Evil`, `MI_Floor_Marble_01`  
**Неверно:** `M_Rock_Snow`, `Rock_Snow_MI`, `MaterialInstance_Rock`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только Material Instance Constant.

## Зачем

В [UE5 Style Guide 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials) для material instances задан префикс MI_; так их легко отличить от базовых материалов (M_) и material functions (MF_).

## Ссылки

- [UE5 Style Guide – 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
