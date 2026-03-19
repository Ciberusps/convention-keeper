# ck-asset-naming-state-tree

Ассеты **StateTree** должны иметь префикс **ST_** (CKConvention).

**Верно:** `ST_AI_Combat`, `ST_Player_Locomotion`, `ST_NPC_Idle`  
**Неверно:** `NewStateTree`, `StateTree_AI`, `BT_Combat`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только ассеты типа StateTree.

## Зачем

StateTree - это ассеты игровой логики, их должно быть легко отличать в Content Browser и в ссылках.
Отдельный префикс `ST_` сохраняет единообразие и снижает путаницу с Behavior Tree (`BT_`) ассетами.

## Ссылки

- [Документация Unreal Engine: StateTree](https://dev.epicgames.com/documentation/en-us/unreal-engine/state-tree-in-unreal-engine)
