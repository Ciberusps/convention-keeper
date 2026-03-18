# asset-naming-enumeration

**Blueprint Enumeration** assets must use the prefix **E** with no underscore (e.g. EWeaponState, EHitResult).

**Valid:** `EWeaponState`, `EHitResult`, `EDamageType`  
**Invalid:** `E_WeaponState`, `WeaponState`, `Enum_WeaponState`

Applies to assets under `Content/{ProjectName}`. Only UserDefinedEnum (Blueprint enumerations) are checked.

## Rationale

The [UE5 Style Guide 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints) uses prefix E with no underscore for enumerations, matching common C++ convention.

## References

- [UE5 Style Guide – 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
