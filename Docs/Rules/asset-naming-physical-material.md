# asset-naming-physical-material

**Physical Material** assets must use the prefix **PM_**.

**Valid:** `PM_Metal_Steel`, `PM_Concrete`, `PM_Glass`, `PM_Wood_01`  
**Invalid:** `M_Metal`, `PhysicalMaterial_Steel`, `PhysMat_Glass`

Applies to assets under `Content/{ProjectName}`. Only Physical Material assets are checked.

## Rationale

The [UE5 Style Guide 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials) uses PM_ for physical materials so they sort and are clearly distinct from rendering materials (M_, MI_).

## References

- [UE5 Style Guide – 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
