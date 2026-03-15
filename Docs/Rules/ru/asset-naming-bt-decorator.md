# asset-naming-bt-decorator

Ассеты **Behavior Tree Decorator** (Blueprint) должны иметь префикс **BTDecorator_**.

**Верно:** `BTDecorator_Cooldown`, `BTDecorator_LineOfSight`, `BTDecorator_HealthCheck`  
**Неверно:** `Decorator_Cooldown`, `BT_CooldownDecorator`, `MyDecorator`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только Blueprint, наследующие BTDecorator_BlueprintBase.

## Ссылки

- [UE5 Style Guide – 1.2.3 Artificial Intelligence](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#123-artificial-intelligence)
