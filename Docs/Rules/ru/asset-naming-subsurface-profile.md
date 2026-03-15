# asset-naming-subsurface-profile

Ассеты **Subsurface Profile** должны иметь префикс **SP_**.

**Верно:** `SP_Skin_Human`, `SP_Wax`, `SP_Marble`  
**Неверно:** `M_Skin_SSS`, `SubsurfaceProfile_Skin`, `SSP_Human`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только Subsurface Profile.

## Зачем

В [UE5 Style Guide 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials) для subsurface profiles задан префикс SP_; так их легко отличить от материалов (M_) и других типов.

## Ссылки

- [UE5 Style Guide – 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
