# asset-naming-aim-offset

**Aim Offset** (1D and 2D) assets must use the prefix **AO_**.

**Valid:** `AO_Character`, `AO_Rifle_1D`, `AO_UpperBody_01`  
**Invalid:** `AimOffset_Character`, `Character_AO`

Applies project-wide under `Content/{ProjectName}`. Only `AimOffsetBlendSpace` and `AimOffsetBlendSpace1D` assets are checked.

## Rationale

[UE5 Style Guide 1.2.2](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) uses **AO_** for both Aim Offset and Aim Offset 1D so they are easy to filter and identify.

## References

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
