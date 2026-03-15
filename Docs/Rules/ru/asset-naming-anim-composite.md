# asset-naming-anim-composite

Ассеты **Animation Composite** должны иметь префикс **AC_**.

**Верно:** `AC_Combo`, `AC_Character_Reactions_01`, `AC_Locomotion_Blend`  
**Неверно:** `Combo`, `AnimComposite_Combo`, `MyComposite`

Правило действует для ассетов в `Content/{ProjectName}` (по всему проекту). Проверяются только ассеты типа AnimComposite.

## Зачем

В [UE5 Style Guide](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) для анимационных композитов задан префикс AC_, чтобы имена были единообразными при поиске и сортировке. Общий шаблон: `Prefix_BaseAssetName_Variant_Suffix`.

## Ссылки

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
