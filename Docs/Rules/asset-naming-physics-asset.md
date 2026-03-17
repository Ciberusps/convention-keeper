# asset-naming-physics-asset

**Physics Asset** (skeletal collision) assets must use the prefix **PHYS_**.

**Valid:** `PHYS_Character`, `PHYS_Weapon_Rifle`, `PHYS_Enemy_Spider`  
**Invalid:** `Character_Physics`, `PhysicsAsset_Character`, `PA_Character`

Applies to assets under `Content/{ProjectName}`. Only Physics Asset assets are checked.

## Rationale

The [UE5 Style Guide 1.2.9 Physics](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#129-physics) uses PHYS_ for physics assets (skeletal body setup) so they sort and are clearly identifiable.

## References

- [UE5 Style Guide – 1.2.9 Physics](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#129-physics)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
