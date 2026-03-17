# asset-naming-anim-sequence

Ассеты **Animation Sequence** должны иметь префикс **A_** (UE5 Style Guide).

**Верно:** `A_Jump`, `A_Character_Idle_01`, `A_Locomotion_Run`  
**Неверно:** `Jump`, `Anim_Jump`, `MySequence`, `AS_Jump` (AS_ используется в [ck-asset-naming-anim-sequence](ck-asset-naming-anim-sequence.md))

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только ассеты типа AnimSequence. Это правило из UE5 Style Guide; **CKConvention** заменяет его на [ck-asset-naming-anim-sequence](ck-asset-naming-anim-sequence.md) (префикс **AS_**).

## Зачем

В [UE5 Style Guide](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) для анимационных последовательностей задан префикс A_. Общий шаблон: `Prefix_BaseAssetName_Variant_Suffix`.

## Ссылки

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
- [ck-asset-naming-anim-sequence](ck-asset-naming-anim-sequence.md) — переопределение в CKConvention (AS_)
