# asset-naming-subsurface-profile

**Subsurface Profile** assets must use the prefix **SP_**.

**Valid:** `SP_Skin_Human`, `SP_Wax`, `SP_Marble`  
**Invalid:** `M_Skin_SSS`, `SubsurfaceProfile_Skin`, `SSP_Human`

Applies to assets under `Content/{ProjectName}`. Only Subsurface Profile assets are checked.

## Rationale

The [UE5 Style Guide 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials) uses SP_ for subsurface profiles so they sort and are distinguishable from materials (M_) and other asset types.

## References

- [UE5 Style Guide – 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
