# asset-naming-static-mesh

**Static Mesh** assets must use the prefix **S_** (not SM_).

**Valid:** `S_Rock_01`, `S_Desk`, `S_Environment_Props`  
**Invalid:** `SM_Rock`, `Rock_01`, `StaticMesh_Desk`

Applies to assets under `Content/{ProjectName}`. Only `StaticMesh` assets are checked.

## Rationale

The [UE5 Style Guide 1.2.1 Most Common](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#121-most-common) specifies the S_ prefix for Static Mesh; the guide notes that many use SM_ but recommends S_.

## References

- [UE5 Style Guide – 1.2.1 Most Common](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#121-most-common)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
