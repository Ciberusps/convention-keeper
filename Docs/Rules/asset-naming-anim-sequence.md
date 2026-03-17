# asset-naming-anim-sequence

**Animation Sequence** assets must use the prefix **A_** (UE5 Style Guide).

**Valid:** `A_Jump`, `A_Character_Idle_01`, `A_Locomotion_Run`  
**Invalid:** `Jump`, `Anim_Jump`, `MySequence`, `AS_Jump` (AS_ is used by [ck-asset-naming-anim-sequence](ck-asset-naming-anim-sequence.md))

Applies to assets under `Content/{ProjectName}`. Only `AnimSequence` assets are checked. This rule is from the UE5 Style Guide; **CKConvention** replaces it with [ck-asset-naming-anim-sequence](ck-asset-naming-anim-sequence.md) (prefix **AS_**).

## Rationale

The [UE5 Style Guide](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) uses a single-letter prefix **A_** for animation sequences. The pattern is `Prefix_BaseAssetName_Variant_Suffix`.

## References

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
- [ck-asset-naming-anim-sequence](ck-asset-naming-anim-sequence.md) — CKConvention override (AS_)
