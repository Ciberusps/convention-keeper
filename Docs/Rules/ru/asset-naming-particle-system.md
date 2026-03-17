# asset-naming-particle-system

Ассеты **Particle System** (Cascade) и **Niagara System** должны иметь префикс **PS_**.

**Верно:** `PS_Explosion`, `PS_MuzzleFlash`, `PS_Environment_Dust`, `PS_Fire_01`  
**Неверно:** `Explosion`, `VFX_Explosion`, `Niagara_Fire`, `Particle_Explosion`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются и Cascade (legacy), и Niagara system.

## Зачем

В [UE5 Style Guide 1.2.12 Effects](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#1212-effects) для particle systems задан префикс PS_; тот же префикс используется для Niagara для единообразия.

## Ссылки

- [UE5 Style Guide – 1.2.12 Effects](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#1212-effects)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
