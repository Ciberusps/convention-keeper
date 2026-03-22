# ec-asset-naming-anim-sequence

**Animation Sequence** assets must use the prefix **AS_** (EarendilConvention).

**Valid:** `AS_Jump`, `AS_Character_Idle_01`, `AS_Locomotion_Run`  
**Invalid:** `Jump`, `A_Jump`, `Anim_Jump`, `MySequence`

Applies to assets under `Content/{ProjectName}`. Only `AnimSequence` assets are checked.

## Rationale

EarendilConvention overrides the [UE5 Style Guide](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations) prefix for animation sequences: the style guide uses **A_**; EarendilConvention uses **AS_** for clarity and consistency with character animation naming (e.g. `AS_{CharacterName}_*`).

## References

- [UE5 Style Guide – 1.2.2 Animations](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
- [asset-naming-character-animations](asset-naming-character-animations.md) (AS_{CharacterName}_* in character folders)
