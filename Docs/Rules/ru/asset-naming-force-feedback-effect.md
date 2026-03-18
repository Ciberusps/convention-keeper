# asset-naming-force-feedback-effect

Ассеты **Force Feedback Effect** должны иметь префикс **FFE_**.

**Верно:** `FFE_WeaponFire`, `FFE_Collision_Heavy`, `FFE_Explosion`  
**Неверно:** `WeaponFire`, `ForceFeedback_Fire`, `MyRumble`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только ассеты типа ForceFeedbackEffect.

## Зачем

В [UE5 Style Guide 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous) для Force Feedback Effect задан префикс FFE_, чтобы ассеты было проще находить и определять по имени.

## Ссылки

- [UE5 Style Guide – 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
