# asset-naming-level-map

Ассеты **Level / Map** (World) могут не иметь суффикса или иметь один из: **_P** (Persistent), **_Audio**, **_Lighting**, **_Geo**, **_Gameplay**.

**Верно:** `MainLevel`, `Campaign_P`, `Arena_Audio`, `Dungeon_Lighting`, `Hub_Geo`, `Battle_Gameplay`  
**Неверно:** `Level_Foo`, `Map_Other`, `Stage_01` (произвольные суффиксы не из списка)

Правило действует для ассетов в `Content/{ProjectName}/Maps`. Проверяются только ассеты типа World. Файлы уровней должны находиться в папке Maps (см. [2.4 Maps](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#24-all-map-files-belong-in-a-folder-called-maps)).

## Зачем

В [UE5 Style Guide 1.2.1 Most Common](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#121-most-common) для подуровней заданы опциональные суффиксы (Persistent, Audio, Lighting, Geometry, Gameplay), чтобы назначение уровня было ясно из имени.

## Ссылки

- [UE5 Style Guide – 1.2.1 Most Common](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#121-most-common)
- [UE5 Style Guide – 2.4 Maps](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#24-all-map-files-belong-in-a-folder-called-maps)
