# asset-naming-level-sequence

Ассеты **Level Sequence** должны иметь префикс **LS_**.

**Верно:** `LS_Intro`, `LS_Gameplay_Cutscene_01`, `LS_Cinematic_Ending`  
**Неверно:** `Intro`, `LevelSequence_Intro`, `MySequence`

Правило действует для ассетов в `Content/{ProjectName}` (по всему проекту). Проверяются только ассеты типа LevelSequence.

## Зачем

В [UE5 Style Guide](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) для level sequence задан префикс LS_, чтобы имена были единообразными при поиске и сортировке. Общий шаблон: `Prefix_BaseAssetName_Variant_Suffix`.

## Ссылки

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
