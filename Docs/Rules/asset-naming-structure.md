# asset-naming-structure

**Blueprint Structure** assets must use the prefix **F** or **S** with no underscore (e.g. FMyStruct, SCharacterData).

**Valid:** `FCharacterData`, `SWeaponConfig`, `FHitResult`  
**Invalid:** `F_CharacterData`, `CharacterData`, `Struct_CharacterData`

Applies to assets under `Content/{ProjectName}`. Only UserDefinedStruct (Blueprint structures) are checked.

## Rationale

The [UE5 Style Guide 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints) uses prefix F or S with no underscore for structures, matching common C++/Unreal convention.

## References

- [UE5 Style Guide – 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
