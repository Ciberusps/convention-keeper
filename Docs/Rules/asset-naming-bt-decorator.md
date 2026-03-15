# asset-naming-bt-decorator

**Behavior Tree Decorator** (Blueprint) assets must use the prefix **BTDecorator_**.

**Valid:** `BTDecorator_Cooldown`, `BTDecorator_LineOfSight`, `BTDecorator_HealthCheck`  
**Invalid:** `Decorator_Cooldown`, `BT_CooldownDecorator`, `MyDecorator`

Applies to assets under `Content/{ProjectName}` (project-wide). Only Blueprints derived from BTDecorator_BlueprintBase are checked.

## Rationale

The [UE5 Style Guide 1.2.3 Artificial Intelligence](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence) uses the BTDecorator_ prefix for behavior tree decorators so they sort and search consistently.

## References

- [UE5 Style Guide – 1.2.3 Artificial Intelligence](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence)
