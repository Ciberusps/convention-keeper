# ck-asset-naming-state-tree

**StateTree** assets must use the prefix **ST_** (CKConvention).

**Valid:** `ST_AI_Combat`, `ST_Player_Locomotion`, `ST_NPC_Idle`  
**Invalid:** `NewStateTree`, `StateTree_AI`, `BT_Combat`

Applies to assets under `Content/{ProjectName}`. Only `StateTree` assets are checked.

## Rationale

StateTree assets are gameplay logic assets and should be easily recognizable in Content Browser and references.
Using a dedicated `ST_` prefix keeps naming consistent and avoids confusion with Behavior Tree (`BT_`) assets.

## References

- [Unreal Engine StateTree documentation](https://dev.epicgames.com/documentation/en-us/unreal-engine/state-tree-in-unreal-engine)
