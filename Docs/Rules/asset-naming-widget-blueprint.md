# asset-naming-widget-blueprint

**Widget Blueprint** (UMG) assets must use the prefix **WBP_**.

**Valid:** `WBP_MainMenu`, `WBP_HealthBar`, `WBP_Inventory_Slot`  
**Invalid:** `MainMenu`, `UI_HealthBar`, `Tet_NewWidgetBlueprint`, `NewWidgetBlueprint`

Applies to assets under `Content/{ProjectName}`. Only Widget Blueprint (UMG) assets are checked.

## Rationale

The [UE5 Style Guide 1.2.11 User Interface](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#1211-user-interface) uses WBP_ for widget blueprints so they sort with other UI assets and are clearly distinct from regular Blueprints (BP_).

## References

- [UE5 Style Guide – 1.2.11 User Interface](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#1211-user-interface)
- [UE5 Style Guide – 1.2.1 Most Common](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#121-most-common) (WBP_ in table)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
