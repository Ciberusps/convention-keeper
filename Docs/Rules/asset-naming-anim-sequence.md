# asset-naming-anim-sequence

**Animation Sequence** assets must use the prefix **A_**.

**Valid:** `A_Jump`, `A_Character_Idle_01`, `A_Locomotion_Run`  
**Invalid:** `Jump`, `Anim_Jump`, `MySequence`

Applies to assets under `Content/{ProjectName}` (project-wide). Only `AnimSequence` assets are checked.

## Rationale

The [UE5 Style Guide](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) uses a single-letter prefix for animation sequences so they sort and search consistently. The pattern is `Prefix_BaseAssetName_Variant_Suffix`.

## References

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
