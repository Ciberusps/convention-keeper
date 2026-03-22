# folder-structure-character-gyms

Для каждого персонажа папка `Content/{ProjectName}/Characters/{CharacterName}/Gyms/` (см. `folder-structure-character`) должна **напрямую** содержать файлы `.uasset` / `.umap` с **базовыми именами** (без расширения) после подстановки плейсхолдеров:

- `Gym_{CharacterName}`
- `AIGym_{CharacterName}`
- `AIGym_{CharacterName}_Arena`
- `AnimGym_{CharacterName}`

Проверка **без рекурсии** (только каталог `Gyms`, не подпапки). Имена ассетов проверяются только если текущий каталог совпадает с разрешённым `FolderPath` правила. В сообщениях — полный путь `Content/.../ИмяАссета` (ссылка в редакторе → `/Game/...`).

## Опции базового правила

Реализовано в `UConventionKeeperRule_FolderStructure`: **RequiredAssets** / **BannedAssets**, **Other Assets Not Allowed** (в правиле Gyms Earendil включено — только четыре нужных ассета в `Gyms/`), **bValidateOnPerAssetSave** (по умолчанию **true**).
