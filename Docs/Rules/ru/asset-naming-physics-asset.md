# asset-naming-physics-asset

Ассеты **Physics Asset** (коллизия скелета) должны иметь префикс **PHYS_**.

**Верно:** `PHYS_Character`, `PHYS_Weapon_Rifle`, `PHYS_Enemy_Spider`  
**Неверно:** `Character_Physics`, `PhysicsAsset_Character`, `PA_Character`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только Physics Asset.

## Зачем

В [UE5 Style Guide 1.2.9 Physics](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#129-physics) для physics assets задан префикс PHYS_; так их легко найти и отличить.

## Ссылки

- [UE5 Style Guide – 1.2.9 Physics](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#129-physics)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
