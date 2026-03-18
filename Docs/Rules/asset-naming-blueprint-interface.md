# asset-naming-blueprint-interface

**Blueprint Interface** assets must use the prefix **BPI_**.

**Valid:** `BPI_Interactable`, `BPI_Damageable`  
**Invalid:** `Interactable`, `BP_Interactable`, `Interface_Interactable`

Applies to assets under `Content/{ProjectName}`. Only Blueprints whose parent is BlueprintInterface are checked.

## Rationale

The [UE5 Style Guide 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints) uses BPI_ for blueprint interfaces so they sort and are clearly identifiable.

## References

- [UE5 Style Guide – 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
