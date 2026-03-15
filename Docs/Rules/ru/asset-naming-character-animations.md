# asset-naming-character-animations

Анимации в `Content/{ProjectName}/Characters/{CharacterName}/Animations` должны называться **AS_{CharacterName}_*** с опциональным нулевым суффиксом (например `AS_Zombie_Jump_01`).

## Зачем

- **AS_** — распространённый префикс «Animation Sequence».
- **{CharacterName}** привязывает ассет к папке персонажа и избегает коллизий между персонажами.
- Нулевой суффикс (например `_01`) сохраняет порядок сортировки и соответствует стайл-гайдам.

## Ссылки

- [UE5 Style Guide – Asset Naming (1.1, 1.2)](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#1-asset-naming-conventions)
- [UE5 Style Guide – Animations (1.2.2)](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
