# asset-naming-enumeration

Ассеты **Blueprint Enumeration** должны иметь префикс **E** без подчёркивания (например EWeaponState, EHitResult).

**Верно:** `EWeaponState`, `EHitResult`, `EDamageType`  
**Неверно:** `E_WeaponState`, `WeaponState`, `Enum_WeaponState`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только UserDefinedEnum (Blueprint-перечисления).

## Зачем

В [UE5 Style Guide 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints) для перечислений задан префикс E без подчёркивания, по аналогии с C++.

## Ссылки

- [UE5 Style Guide – 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
