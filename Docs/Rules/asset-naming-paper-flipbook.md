# asset-naming-paper-flipbook

**Paper Flipbook** assets must use the prefix **PFB_**.

**Valid:** `PFB_Character_Run`, `PFB_Enemy_Explode_01`, `PFB_Prop_Door`  
**Invalid:** `Run`, `Flipbook_Run`, `MyFlipbook`

Applies to assets under `Content/{ProjectName}` (project-wide). Only `PaperFlipbook` assets are checked.

## Rationale

The [UE5 Style Guide](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) uses the PFB_ prefix for paper flipbooks so they sort and search consistently. The pattern is `Prefix_BaseAssetName_Variant_Suffix`.

## References

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
