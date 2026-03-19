# asset-naming-static-mesh

Ассеты **Static Mesh** должны иметь префикс **S_** (не SM_).

**Верно:** `S_Rock_01`, `S_Desk`, `S_Environment_Props`  
**Неверно:** `SM_Rock`, `Rock_01`, `StaticMesh_Desk`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только ассеты типа StaticMesh.

## Зачем

В [UE5 Style Guide 1.2.1 Most Common](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#121-most-common) для Static Mesh задан префикс S_; в гайде указано, что многие используют SM_, но рекомендуется S_.

## Ссылки

- [UE5 Style Guide – 1.2.1 Most Common](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#121-most-common)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
