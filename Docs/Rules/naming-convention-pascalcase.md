# naming-convention-pascalcase

Folder and asset names must be **PascalCase**: each segment (after splitting by underscore) starts with an uppercase letter, the rest are lowercase letters or digits. Acronyms like `BP`, `M`, `T` are allowed as all-caps segments.

**Valid:** `MyFolder`, `BP_MyActor`, `M_MyMaterial`, `Characters`, `AS_Zombie_Jump_01`  
**Invalid:** `myFolder`, `bp_MyActor`, `my_asset`, `folder-name`

Applies to the path scope set in the rule (default: `Content/{ProjectName}`). Both folder segment names and asset names are checked.

## Rationale

PascalCase keeps names consistent with Unreal and UE5 Style Guide: no spaces, no hyphens, clear word boundaries. Prefixes like `BP_`, `M_` are part of the convention; each segment still starts with a capital.

## Base rule type

This rule is an instance of **Rule_NamingConvention**. Other naming rules (e.g. custom formats) can subclass `UConventionKeeperRule_NamingConvention` and implement `IsNameValidForFolder` / `IsNameValidForAsset`.

## References

- [UE5 Style Guide – 2.1 Folder Names (PascalCase)](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#21-folder-names)
- [UE5 Style Guide – Content Directory Structure](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#2-content-directory-structure)
