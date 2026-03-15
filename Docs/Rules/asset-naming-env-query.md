# asset-naming-env-query

**Environment Query** assets must use the prefix **EQS_**.

**Valid:** `EQS_FindCover`, `EQS_NearestEnemy`, `EQS_PatrolPoints`  
**Invalid:** `FindCover`, `EnvQuery_FindCover`, `MyEQS`

Applies to assets under `Content/{ProjectName}` (project-wide). Only Environment Query assets are checked.

## Rationale

The [UE5 Style Guide 1.2.3 Artificial Intelligence](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence) uses the EQS_ prefix for environment queries so they sort and search consistently.

## References

- [UE5 Style Guide – 1.2.3 Artificial Intelligence](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence)
