# asset-naming-ai-controller

Ассеты **AI Controller** (Blueprint) должны иметь префикс **AIC_**.

**Верно:** `AIC_Enemy`, `AIC_Turret_01`, `AIC_Boss_Spider`  
**Неверно:** `EnemyController`, `BP_AIController`, `MyAI`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только Blueprint, наследующие AIController.

## Ссылки

- [UE5 Style Guide – 1.2.3 Artificial Intelligence](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence)
