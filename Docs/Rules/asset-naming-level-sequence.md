# asset-naming-level-sequence

**Level Sequence** assets must use the prefix **LS_**.

**Valid:** `LS_Intro`, `LS_Gameplay_Cutscene_01`, `LS_Cinematic_Ending`  
**Invalid:** `Intro`, `LevelSequence_Intro`, `MySequence`

Applies to assets under `Content/{ProjectName}` (project-wide). Only `LevelSequence` assets are checked.

## Rationale

The [UE5 Style Guide](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) uses the LS_ prefix for level sequences so they sort and search consistently. The pattern is `Prefix_BaseAssetName_Variant_Suffix`.

## References

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
