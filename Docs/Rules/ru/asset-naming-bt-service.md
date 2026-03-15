# asset-naming-bt-service

Ассеты **Behavior Tree Service** (Blueprint) должны иметь префикс **BTService_**.

**Верно:** `BTService_UpdateTarget`, `BTService_ScanEnemies`, `BTService_UpdateHealth`  
**Неверно:** `Service_UpdateTarget`, `BT_UpdateTargetService`, `MyService`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только Blueprint, наследующие BTService_BlueprintBase.

## Ссылки

- [UE5 Style Guide – 1.2.3 Artificial Intelligence](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence)
