# asset-placement-maps

Ассеты **Level / Map** (World) должны находиться в папке с именем **Maps**.

**Верный путь:** `Content/{ProjectName}/Maps/MainLevel`, `Content/{ProjectName}/Maps/Campaign1/Arena_01`  
**Неверный путь:** `Content/{ProjectName}/Levels/MainLevel`, `Content/{ProjectName}/Art/TestMap`

Правило действует для всех ассетов World в `Content/{ProjectName}`. Именование карт проверяется отдельным правилом [asset-naming-level-map](asset-naming-level-map.md).

## Зачем

В [UE5 Style Guide 2.4](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#24-all-map-files-belong-in-a-folder-called-maps) указано, что все файлы карт должны находиться в папке Maps. Это упрощает кукинг, скрипты освещения и QA, а также позволяет однозначно указать, где искать карту.

## Ссылки

- [UE5 Style Guide – 2.4 All Map Files Belong In A Folder Called Maps](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#24-all-map-files-belong-in-a-folder-called-maps)
- [UE5 Style Guide – 2. Content Directory Structure](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#2-content-directory-structure)
