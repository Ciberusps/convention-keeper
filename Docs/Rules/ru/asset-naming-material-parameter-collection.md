# asset-naming-material-parameter-collection

Ассеты **Material Parameter Collection** должны иметь префикс **MPC_**.

**Верно:** `MPC_Weather`, `MPC_Global_Colors`, `MPC_TimeOfDay`  
**Неверно:** `M_Weather_Params`, `MaterialParameterCollection_Global`, `MP_Colors`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только Material Parameter Collection.

## Зачем

В [UE5 Style Guide 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials) для material parameter collections задан префикс MPC_; по имени сразу видно тип ассета.

## Ссылки

- [UE5 Style Guide – 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
