# asset-naming-anim-composite

**Animation Composite** assets must use the prefix **AC_**.

**Valid:** `AC_Combo`, `AC_Character_Reactions_01`, `AC_Locomotion_Blend`  
**Invalid:** `Combo`, `AnimComposite_Combo`, `MyComposite`

Applies to assets under `Content/{ProjectName}` (project-wide). Only `AnimComposite` assets are checked.

## Rationale

The [UE5 Style Guide](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) uses the AC_ prefix for animation composites so they sort and search consistently. The pattern is `Prefix_BaseAssetName_Variant_Suffix`.

## References

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
