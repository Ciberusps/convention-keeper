# asset-naming-material

**Material** assets must use prefix **M_** (Surface/Default) or **PP_** (Post Process), depending on the material's **Material Domain**.

The rule inspects each asset: if `MaterialDomain == Post Process`, the required prefix is **PP_**; otherwise **M_**.

**Valid:** `M_Character_Skin`, `M_Rock`, `PP_Vignette`, `PP_ColorGrading`  
**Invalid:** `CharacterMaterial`, `PostProcess_Blur` (use PP_ for post process), `M_Blur` when domain is Post Process (use PP_)

Applies to assets under `Content/{ProjectName}`. Only Material assets are checked.

## Rationale

The [UE5 Style Guide 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials) uses M_ for regular materials and PP_ for post process materials so they sort and are identifiable by domain without opening the asset.

## References

- [UE5 Style Guide – 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
