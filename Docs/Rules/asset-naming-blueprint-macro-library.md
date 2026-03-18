# asset-naming-blueprint-macro-library

**Blueprint Macro Library** assets must use the prefix **BPML_**. The style guide recommends avoiding macro libraries when possible.

**Valid:** `BPML_CommonMacros`, `BPML_EditorHelpers`  
**Invalid:** `CommonMacros`, `BP_CommonMacros`, `BML_Macros`

Applies to assets under `Content/{ProjectName}`. Only Blueprints whose parent is BlueprintMacroLibrary are checked.

## Rationale

The [UE5 Style Guide 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints) uses BPML_ for blueprint macro libraries. Prefer function libraries (BPFL_) when possible.

## References

- [UE5 Style Guide – 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
