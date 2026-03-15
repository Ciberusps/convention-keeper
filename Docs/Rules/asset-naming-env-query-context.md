# asset-naming-env-query-context

**Env Query Context** (Blueprint) assets must use the prefix **EQS_** and the suffix **Context**.

**Valid:** `EQS_PlayerContext`, `EQS_EnemyContext`, `EQS_ItemContext`  
**Invalid:** `PlayerContext`, `EQS_Player`, `EnvQueryContext_Player`

Applies to assets under `Content/{ProjectName}` (project-wide). Only Blueprints derived from EnvQueryContext are checked.

## Rationale

The [UE5 Style Guide 1.2.3 Artificial Intelligence](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence) uses the EQS_ prefix and Context suffix for env query contexts so they sort and search consistently.

## References

- [UE5 Style Guide – 1.2.3 Artificial Intelligence](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence)
