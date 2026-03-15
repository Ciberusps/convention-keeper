# asset-naming-bt-task

Ассеты **Behavior Tree Task** (Blueprint) должны иметь префикс **BTTask_**.

**Верно:** `BTTask_MoveToTarget`, `BTTask_Attack`, `BTTask_PlayAnimation`  
**Неверно:** `Task_MoveToTarget`, `BT_MoveToTargetTask`, `MyTask`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только Blueprint, наследующие BTTask_BlueprintBase.

## Ссылки

- [UE5 Style Guide – 1.2.3 Artificial Intelligence](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence)
