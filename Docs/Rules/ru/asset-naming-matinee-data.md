# asset-naming-matinee-data

Ассеты **Matinee Data** (InterpData) должны иметь префикс **Matinee_**.

**Верно:** `Matinee_Intro`, `Matinee_Cutscene`, `Matinee_Door_01`  
**Неверно:** `Intro`, `InterpData_Intro`, `MatineeIntro`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только ассеты типа Matinee Data (InterpData).

## Зачем

В [UE5 Style Guide 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous) для Matinee Data задан префикс Matinee_, чтобы такие ассеты было проще находить при работе с устаревшими последовательностями Matinee.

## Ссылки

- [UE5 Style Guide – 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
