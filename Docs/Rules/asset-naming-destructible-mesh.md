# asset-naming-destructible-mesh

**Destructible Mesh** (legacy Apex Destruction) assets must use the prefix **DM_**.

**Valid:** `DM_Barrel`, `DM_Wall_Concrete`, `DM_Crate_01`  
**Invalid:** `Barrel_Destructible`, `DestructibleMesh_Wall`, `Barrel`

Applies to assets under `Content/{ProjectName}`. Only Destructible Mesh assets (Apex Destruction plugin) are checked. In UE5, Chaos destruction typically uses Geometry Collection assets instead.

## Rationale

The [UE5 Style Guide 1.2.9 Physics](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#129-physics) uses DM_ for destructible mesh assets so they sort and are clearly identifiable.

## References

- [UE5 Style Guide – 1.2.9 Physics](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#129-physics)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
