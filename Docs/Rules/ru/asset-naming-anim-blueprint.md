# asset-naming-anim-blueprint

Ассеты **Animation Blueprint** должны иметь префикс **ABP_**.

**Верно:** `ABP_Character`, `ABP_Zombie_Locomotion`, `ABP_Player`  
**Неверно:** `BP_Anim_Character`, `AnimBlueprint_Character`

Правило действует по всему проекту в `Content/{ProjectName}`. Проверяются только ассеты AnimBlueprint.

## Зачем

[UE5 Style Guide 1.2.2](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) задаёт префикс **ABP_** для анимационных блюпринтов, чтобы отличать их от обычных BP_ и сохранять единый стиль имён.

## Ссылки

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
