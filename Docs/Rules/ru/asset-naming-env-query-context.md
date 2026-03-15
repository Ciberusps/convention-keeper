# asset-naming-env-query-context

Ассеты **Env Query Context** (Blueprint) должны иметь префикс **EQS_** и суффикс **Context**.

**Верно:** `EQS_PlayerContext`, `EQS_EnemyContext`, `EQS_ItemContext`  
**Неверно:** `PlayerContext`, `EQS_Player`, `EnvQueryContext_Player`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только Blueprint, наследующие EnvQueryContext.

## Ссылки

- [UE5 Style Guide – 1.2.3 Artificial Intelligence](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence)
