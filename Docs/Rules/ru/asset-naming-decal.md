# asset-naming-decal

Материалы **Decal** (Material или Material Instance с **Material Domain = Deferred Decal**) должны иметь префикс **M_** (для базового Material) или **MI_** (для Material Instance) и суффикс **_Decal**.

Правило применяется только к ассетам, которые действительно являются декалями: базовые материалы с `MaterialDomain == Deferred Decal` и material instances, чей базовый материал — декаль. Остальные материалы этим правилом не проверяются.

**Верно:** `M_BloodSplatter_Decal`, `MI_Dirt_Decal`, `M_Damage_Decal`  
**Неверно:** `M_BloodSplatter` (нет _Decal), `Decal_Blood` (неверный префикс), `MI_Dirt` (декали должны заканчиваться на _Decal)

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только декаль-материалы и декаль material instances.

## Зачем

В [UE5 Style Guide 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials) для декалей заданы префикс M_ или MI_ и суффикс _Decal; по имени сразу видно назначение и сортировка единообразна.

## Ссылки

- [UE5 Style Guide – 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
