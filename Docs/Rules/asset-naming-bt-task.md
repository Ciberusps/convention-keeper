# asset-naming-bt-task

**Behavior Tree Task** (Blueprint) assets must use the prefix **BTTask_**.

**Valid:** `BTTask_MoveToTarget`, `BTTask_Attack`, `BTTask_PlayAnimation`  
**Invalid:** `Task_MoveToTarget`, `BT_MoveToTargetTask`, `MyTask`

Applies to assets under `Content/{ProjectName}` (project-wide). Only Blueprints derived from BTTask_BlueprintBase are checked.

## Rationale

The [UE5 Style Guide 1.2.3 Artificial Intelligence](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence) uses the BTTask_ prefix for behavior tree tasks so they sort and search consistently.

## References

- [UE5 Style Guide – 1.2.3 Artificial Intelligence](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence)
