# asset-naming-texture

**Texture** assets must use the prefix that matches their type. Optional suffix for **T_** textures must be one or more letters from the style guide set.

## Prefix by type

| Type | Prefix | Example |
|------|--------|---------|
| Texture 2D | **T_** | T_Bob_D, T_Rock_N, T_Noise_ERO |
| Texture Cube | **TC_** | TC_Sky, TC_Reflection |
| Media Texture | **MT_** | MT_Webcam |
| Render Target 2D | **RT_** | RT_SceneCapture |
| Cube Render Target | **RTC_** | RTC_Reflection |
| Texture Light Profile | **TLP_** | TLP_Soft |

## Suffix for T_ (Texture 2D)

If the name has a suffix after the base name, it must be composed only of letters: **D, N, R, A, O, B, E, M, S** (one or more). These match the style guide: _D (Diffuse/Albedo), _N (Normal), _R (Roughness), _A (Alpha), _O (Ambient Occlusion), _B (Bump), _E (Emissive), _M (Mask/Metallic), _S (Specular). Packed textures use multiple letters (e.g. _ERO).

**Valid:** `T_Character_D`, `T_Rock_N`, `T_Noise_ERO`, `T_Material`, `TC_Sky`, `RT_Buffer`  
**Invalid:** `Character_D` (missing T_), `T_Character_X` (X not allowed), `Texture_Rock` (wrong prefix)

Applies to assets under `Content/{ProjectName}`. All texture types (Texture2D, TextureCube, Media Texture, Render Target, Cube Render Target, Texture Light Profile) are checked.

## References

- [UE5 Style Guide – 1.2.6 Textures](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#126-textures)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
