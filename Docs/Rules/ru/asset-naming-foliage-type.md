# asset-naming-foliage-type

Ассеты **Foliage Type** должны иметь префикс **FT_**.

**Верно:** `FT_Grass_01`, `FT_Tree_Oak`, `FT_Bush_Desert`  
**Неверно:** `Grass_01`, `FoliageType_Tree`, `MyFoliage`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только ассеты типа Foliage Type (instanced static mesh и actor).

## Зачем

В [UE5 Style Guide 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous) для Foliage Type задан префикс FT_, чтобы ассеты единообразно сортировались и фильтровались в content browser.

## Ссылки

- [UE5 Style Guide – 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
