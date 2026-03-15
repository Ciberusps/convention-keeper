# asset-naming-control-rig

Ассеты **Control Rig** должны иметь префикс **CR_**.

**Верно:** `CR_Character_Spine`, `CR_Weapon_IK_01`, `CR_Facial_Rig`  
**Неверно:** `CharacterRig`, `ControlRig_Spine`, `MyRig`

Правило действует для ассетов в `Content/{ProjectName}` (по всему проекту). Проверяются только ассеты Control Rig Blueprint.

## Зачем

В [UE5 Style Guide](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) для control rig задан префикс CR_, чтобы имена были единообразными при поиске и сортировке. Общий шаблон: `Prefix_BaseAssetName_Variant_Suffix`.

## Ссылки

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
