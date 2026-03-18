# asset-naming-blueprint-function-library

**Blueprint Function Library** assets must use the prefix **BPFL_**.

**Valid:** `BPFL_GameHelpers`, `BPFL_MathUtils`  
**Invalid:** `GameHelpers`, `BP_GameHelpers`, `BFL_Utils`

Applies to assets under `Content/{ProjectName}`. Only Blueprints whose parent is BlueprintFunctionLibrary are checked.

## Rationale

The [UE5 Style Guide 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints) uses BPFL_ for blueprint function libraries so they sort and are clearly identifiable.

## References

- [UE5 Style Guide – 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
