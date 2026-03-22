# ec-asset-naming-anim-sequence

Ассеты **Animation Sequence** должны иметь префикс **AS_** (EarendilConvention).

**Верно:** `AS_Jump`, `AS_Character_Idle_01`, `AS_Locomotion_Run`  
**Неверно:** `Jump`, `A_Jump`, `Anim_Jump`, `MySequence`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только ассеты типа AnimSequence.

## Зачем

EarendilConvention переопределяет префикс из [UE5 Style Guide](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations): в гайде используется **A_**, в EarendilConvention — **AS_** для единообразия с именами анимаций персонажей (например `AS_{CharacterName}_*`).

## Ссылки

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
- [asset-naming-character-animations](asset-naming-character-animations.md) (AS_{CharacterName}_* в папках персонажей)
