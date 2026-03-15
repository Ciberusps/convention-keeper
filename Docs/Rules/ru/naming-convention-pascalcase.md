# naming-convention-pascalcase

Имена папок и ассетов должны быть в **PascalCase**: каждый сегмент (после разбиения по подчёркиванию) начинается с заглавной буквы, остальные символы — строчные буквы или цифры. Допускаются акронимы вроде `BP`, `M`, `T` как сегменты из заглавных.

**Верно:** `MyFolder`, `BP_MyActor`, `M_MyMaterial`, `Characters`, `AS_Zombie_Jump_01`  
**Неверно:** `myFolder`, `bp_MyActor`, `my_asset`, `folder-name`

Действует в пределах пути, заданного в правиле (по умолчанию: `Content/{ProjectName}`). Проверяются и имена сегментов папок, и имена ассетов.

## Зачем

PascalCase согласуется с Unreal и UE5 Style Guide: без пробелов и дефисов, чёткие границы слов. Префиксы вроде `BP_`, `M_` — часть конвенции; каждый сегмент по-прежнему начинается с заглавной.

## Базовый тип правила

Это правило — экземпляр **Rule_NamingConvention**. Другие правила именования могут наследовать `UConventionKeeperRule_NamingConvention` и реализовать `IsNameValidForFolder` / `IsNameValidForAsset`.

## Ссылки

- [UE5 Style Guide – 2.1 Folder Names (PascalCase)](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#21-folder-names)
- [UE5 Style Guide – Content Directory Structure](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#2-content-directory-structure)
