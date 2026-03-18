# asset-naming-blueprint-component

**Blueprint Component** assets must use the prefix **BP_** and the suffix **Component** (e.g. BP_InventoryComponent).

**Valid:** `BP_InventoryComponent`, `BP_HealthComponent`  
**Invalid:** `BP_Inventory`, `InventoryComponent`, `BP_MyComponent_Extra`

Applies to assets under `Content/{ProjectName}`. Only Blueprints whose parent is ActorComponent (or a subclass) are checked.

## Rationale

The [UE5 Style Guide 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints) uses BP_ and suffix Component for blueprint components.

## References

- [UE5 Style Guide – 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
