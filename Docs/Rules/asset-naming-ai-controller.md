# asset-naming-ai-controller

**AI Controller** (Blueprint) assets must use the prefix **AIC_**.

**Valid:** `AIC_Enemy`, `AIC_Turret_01`, `AIC_Boss_Spider`  
**Invalid:** `EnemyController`, `BP_AIController`, `MyAI`

Applies to assets under `Content/{ProjectName}` (project-wide). Only Blueprints derived from AIController are checked.

## Rationale

The [UE5 Style Guide 1.2.3 Artificial Intelligence](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence) uses the AIC_ prefix for AI Controller Blueprints so they sort and search consistently.

## References

- [UE5 Style Guide – 1.2.3 Artificial Intelligence](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence)
