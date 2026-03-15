# asset-naming-material-function

Ассеты **Material Function** должны иметь префикс **MF_**.

**Верно:** `MF_Utility_Noise`, `MF_Blend_Overlay`, `MF_VertexColor_Blend`  
**Неверно:** `M_Noise`, `MaterialFunction_Blend`, `NoiseFunction`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только Material Function.

## Зачем

В [UE5 Style Guide 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials) для material functions задан префикс MF_; так их легко отличить от материалов (M_) и инстансов (MI_).

## Ссылки

- [UE5 Style Guide – 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
