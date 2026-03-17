# asset-naming-particle-system

**Particle System** (Cascade) and **Niagara System** assets must use the prefix **PS_**.

**Valid:** `PS_Explosion`, `PS_MuzzleFlash`, `PS_Environment_Dust`, `PS_Fire_01`  
**Invalid:** `Explosion`, `VFX_Explosion`, `Niagara_Fire`, `Particle_Explosion`

Applies to assets under `Content/{ProjectName}`. Both Cascade (legacy) and Niagara system assets are checked.

## Rationale

The [UE5 Style Guide 1.2.12 Effects](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#1212-effects) uses PS_ for particle systems so they sort and are clearly identifiable. The same prefix applies to Niagara systems for consistency.

## References

- [UE5 Style Guide – 1.2.12 Effects](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#1212-effects)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
