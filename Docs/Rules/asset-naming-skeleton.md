# asset-naming-skeleton

**Skeleton** assets must use the prefix **SKEL_**.

**Valid:** `SKEL_Character_Human`, `SKEL_Enemy_Spider`, `SKEL_Weapon_Rifle`  
**Invalid:** `Human`, `Skeleton_Human`, `MySkeleton`

Applies to assets under `Content/{ProjectName}` (project-wide). Only `Skeleton` assets are checked.

## Rationale

The [UE5 Style Guide](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) uses the SKEL_ prefix for skeletons so they sort and search consistently. The pattern is `Prefix_BaseAssetName_Variant_Suffix`.

## References

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
