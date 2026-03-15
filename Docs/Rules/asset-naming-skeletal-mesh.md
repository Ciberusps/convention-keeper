# asset-naming-skeletal-mesh

**Skeletal Mesh** assets must use the prefix **SK_**.

**Valid:** `SK_Character_Hero`, `SK_Enemy_Zombie_01`, `SK_Weapon_Sword`  
**Invalid:** `Hero`, `SkeletalMesh_Hero`, `MyMesh`

Applies to assets under `Content/{ProjectName}` (project-wide). Only `SkeletalMesh` assets are checked.

## Rationale

The [UE5 Style Guide](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) uses the SK_ prefix for skeletal meshes so they sort and search consistently. The pattern is `Prefix_BaseAssetName_Variant_Suffix`.

## References

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
