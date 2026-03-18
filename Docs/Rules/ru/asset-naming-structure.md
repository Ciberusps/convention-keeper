# asset-naming-structure

Ассеты **Blueprint Structure** должны иметь префикс **F** или **S** без подчёркивания (например FMyStruct, SCharacterData).

**Верно:** `FCharacterData`, `SWeaponConfig`, `FHitResult`  
**Неверно:** `F_CharacterData`, `CharacterData`, `Struct_CharacterData`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только UserDefinedStruct (Blueprint-структуры).

## Зачем

В [UE5 Style Guide 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints) для структур заданы префиксы F или S без подчёркивания, по аналогии с C++/Unreal.

## Ссылки

- [UE5 Style Guide – 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
