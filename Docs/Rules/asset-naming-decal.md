# asset-naming-decal

**Decal** materials (Material or Material Instance with **Material Domain = Deferred Decal**) must use prefix **M_** (for base Material) or **MI_** (for Material Instance) and suffix **_Decal**.

The rule applies only to assets that are actually decals: base materials with `MaterialDomain == Deferred Decal`, and material instances whose base material is a decal. Other materials are not checked by this rule.

**Valid:** `M_BloodSplatter_Decal`, `MI_Dirt_Decal`, `M_Damage_Decal`  
**Invalid:** `M_BloodSplatter` (missing _Decal), `Decal_Blood` (wrong prefix), `MI_Dirt` (decals must end with _Decal)

Applies to assets under `Content/{ProjectName}`. Only decal Materials and decal Material Instances are validated.

## Rationale

The [UE5 Style Guide 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials) specifies that decals use M_ or MI_ with suffix _Decal so they are identifiable and sort consistently.

## References

- [UE5 Style Guide – 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
