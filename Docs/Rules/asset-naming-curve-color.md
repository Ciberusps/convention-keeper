# asset-naming-curve-color

**Color Curve** assets must use the prefix **Curve_** and the suffix **_Color**.

**Valid:** `Curve_UIHighlight_Color`, `Curve_AmbientTint_Color`  
**Invalid:** `UIHighlight`, `Curve_UIHighlight`, `ColorCurve_Ambient`

Applies to assets under `Content/{ProjectName}`. Only `CurveLinearColor` assets are checked.

## Rationale

The [UE5 Style Guide 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous) specifies prefix Curve_ and suffix _Color for color curves so curve type is clear from the name.

## References

- [UE5 Style Guide – 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
