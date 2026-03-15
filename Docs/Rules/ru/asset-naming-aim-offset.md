# asset-naming-aim-offset

Ассеты **Aim Offset** (1D и 2D) должны иметь префикс **AO_**.

**Верно:** `AO_Character`, `AO_Rifle_1D`, `AO_UpperBody_01`  
**Неверно:** `AimOffset_Character`, `Character_AO`

Правило действует по всему проекту в `Content/{ProjectName}`. Проверяются только ассеты AimOffsetBlendSpace и AimOffsetBlendSpace1D.

## Зачем

[UE5 Style Guide 1.2.2](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) задаёт префикс **AO_** для обоих типов Aim Offset для удобного поиска и идентификации.

## Ссылки

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
