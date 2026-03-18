# asset-naming-static-vector-field

**Static Vector Field** assets must use the prefix **VF_**.

**Valid:** `VF_Wind`, `VF_Vortex`, `VF_Flow_01`  
**Invalid:** `Wind`, `VectorField_Wind`, `VFA_Wind`

Applies to assets under `Content/{ProjectName}`. Only Static Vector Field assets are checked.

## Rationale

The [UE5 Style Guide 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous) specifies the VF_ prefix for Static Vector Field assets so they are easy to identify and distinguish from Animated Vector Fields (VFA_).

## References

- [UE5 Style Guide – 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
