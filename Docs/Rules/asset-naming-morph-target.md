# asset-naming-morph-target

**Morph Target** assets must use the prefix **MT_**.

**Valid:** `MT_Character_Smile`, `MT_Face_Blink_01`, `MT_Body_Squash`  
**Invalid:** `Smile`, `MorphTarget_Smile`, `MyMorph`

Applies to assets under `Content/{ProjectName}` (project-wide). Only `MorphTarget` assets are checked.

## Rationale

The [UE5 Style Guide](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) uses the MT_ prefix for morph targets so they sort and search consistently. The pattern is `Prefix_BaseAssetName_Variant_Suffix`.

## References

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
