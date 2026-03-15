# asset-naming-skeleton

Ассеты **Skeleton** должны иметь префикс **SKEL_**.

**Верно:** `SKEL_Character_Human`, `SKEL_Enemy_Spider`, `SKEL_Weapon_Rifle`  
**Неверно:** `Human`, `Skeleton_Human`, `MySkeleton`

Правило действует для ассетов в `Content/{ProjectName}` (по всему проекту). Проверяются только ассеты типа Skeleton.

## Зачем

В [UE5 Style Guide](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) для скелета задан префикс SKEL_, чтобы имена были единообразными при поиске и сортировке. Общий шаблон: `Prefix_BaseAssetName_Variant_Suffix`.

## Ссылки

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
