# asset-naming-destructible-mesh

Ассеты **Destructible Mesh** (legacy Apex Destruction) должны иметь префикс **DM_**.

**Верно:** `DM_Barrel`, `DM_Wall_Concrete`, `DM_Crate_01`  
**Неверно:** `Barrel_Destructible`, `DestructibleMesh_Wall`, `Barrel`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только Destructible Mesh (плагин Apex Destruction). В UE5 для разрушений обычно используют Geometry Collection.

## Зачем

В [UE5 Style Guide 1.2.9 Physics](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#129-physics) для destructible mesh задан префикс DM_.

## Ссылки

- [UE5 Style Guide – 1.2.9 Physics](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#129-physics)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
