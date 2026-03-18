# asset-naming-curve-float

**Float Curve** assets must use the prefix **Curve_** and the suffix **_Float**.

**Valid:** `Curve_DamageOverTime_Float`, `Curve_HealthRegen_Float`  
**Invalid:** `DamageOverTime`, `Curve_HealthRegen`, `FloatCurve_Health`

Applies to assets under `Content/{ProjectName}`. Only `CurveFloat` assets are checked.

## Rationale

The [UE5 Style Guide 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous) specifies prefix Curve_ and suffix _Float for float curves so curve type is clear from the name.

## References

- [UE5 Style Guide – 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
