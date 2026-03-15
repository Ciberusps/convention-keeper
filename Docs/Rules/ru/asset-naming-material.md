# asset-naming-material

Ассеты **Material** должны иметь префикс **M_** (Surface/Default) или **PP_** (Post Process) в зависимости от **Material Domain** материала.

Правило проверяет каждый ассет: если `MaterialDomain == Post Process`, требуется префикс **PP_**; иначе **M_**.

**Верно:** `M_Character_Skin`, `M_Rock`, `PP_Vignette`, `PP_ColorGrading`  
**Неверно:** `CharacterMaterial`, `PostProcess_Blur` (для post process нужен PP_), `M_Blur` при домене Post Process (нужен PP_)

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только материалы (Material).

## Зачем

В [UE5 Style Guide 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials) для обычных материалов используется M_, для постпроцесса — PP_; по префиксу можно определить тип без открытия ассета.

## Ссылки

- [UE5 Style Guide – 1.2.5 Materials](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#125-materials)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
