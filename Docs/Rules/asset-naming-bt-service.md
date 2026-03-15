# asset-naming-bt-service

**Behavior Tree Service** (Blueprint) assets must use the prefix **BTService_**.

**Valid:** `BTService_UpdateTarget`, `BTService_ScanEnemies`, `BTService_UpdateHealth`  
**Invalid:** `Service_UpdateTarget`, `BT_UpdateTargetService`, `MyService`

Applies to assets under `Content/{ProjectName}` (project-wide). Only Blueprints derived from BTService_BlueprintBase are checked.

## Rationale

The [UE5 Style Guide 1.2.3 Artificial Intelligence](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence) uses the BTService_ prefix for behavior tree services so they sort and search consistently.

## References

- [UE5 Style Guide – 1.2.3 Artificial Intelligence](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence)
