# asset-naming-control-rig

**Control Rig / Rig** assets must use the prefix **CR_** or **Rig_**.

**Valid:** `CR_Character_Spine`, `Rig_Weapon_IK_01`, `Rig_Facial_Rig`  
**Invalid:** `CharacterRig`, `ControlRig_Spine`, `MyRig`

Applies to assets under `Content/{ProjectName}` (project-wide). Only Control Rig Blueprint assets are checked.

## Rationale

The [UE5 Style Guide](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) uses the CR_ prefix for control rigs and Rig_ for rigs so they sort and search consistently. The pattern is `Prefix_BaseAssetName_Variant_Suffix`.

## References

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
