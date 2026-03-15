# asset-naming-material-instance

**Material Instance** assets must use the prefix **MI_**.

**Valid:** `MI_Rock_Snow`, `MI_Character_Evil`, `MI_Floor_Marble_01`  
**Invalid:** `M_Rock_Snow`, `Rock_Snow_MI`, `MaterialInstance_Rock`

Applies to assets under `Content/{ProjectName}`. Only Material Instance Constant assets are checked.

## Rationale

The [UE5 Style Guide 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials) uses MI_ for material instances so they sort and are clearly distinct from base materials (M_) and material functions (MF_).

## References

- [UE5 Style Guide – 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
