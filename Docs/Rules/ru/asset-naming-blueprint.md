# asset-naming-blueprint

Ассеты **Blueprint** и **Tutorial Blueprint** должны иметь префикс **BP_** или **TBP_**.

**Верно:** `BP_PlayerCharacter`, `BP_Barrel`, `TBP_IntroSequence`  
**Неверно:** `PlayerCharacter`, `MyBlueprint`, `Tutorial_Intro`

Правило действует для ассетов в `Content/{ProjectName}`. Не применяется к Blueprint Function Library (BPFL_), Blueprint Interface (BPI_), Blueprint Macro Library (BPML_), Blueprint Component (BP_*Component), AI Controller (AIC_), типам Behavior Tree (BT*, EQS*) и Widget Blueprint (WBP_).

## Зачем

В [UE5 Style Guide 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints) для Blueprint заданы префиксы BP_ и TBP_.

## Ссылки

- [UE5 Style Guide – 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
