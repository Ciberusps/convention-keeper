# asset-naming-anim-blueprint

**Animation Blueprint** assets must use the prefix **ABP_**.

**Valid:** `ABP_Character`, `ABP_Zombie_Locomotion`, `ABP_Player`  
**Invalid:** `BP_Anim_Character`, `AnimBlueprint_Character`

Applies project-wide under `Content/{ProjectName}`. Only `AnimBlueprint` assets are checked.

## Rationale

[UE5 Style Guide 1.2.2](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) uses **ABP_** for Animation Blueprints to distinguish them from regular Blueprints (BP_) and to keep naming consistent.

## References

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
