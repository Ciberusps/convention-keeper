# asset-naming-behavior-tree

**Behavior Tree** assets must use the prefix **BT_**.

**Valid:** `BT_Enemy_Melee`, `BT_Turret_01`, `BT_Boss_Phase1`  
**Invalid:** `EnemyTree`, `BehaviorTree_Enemy`, `MyBT`

Applies to assets under `Content/{ProjectName}` (project-wide). Only Behavior Tree assets are checked.

## Rationale

The [UE5 Style Guide 1.2.3 Artificial Intelligence](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence) uses the BT_ prefix for behavior trees so they sort and search consistently.

## References

- [UE5 Style Guide – 1.2.3 Artificial Intelligence](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence)
