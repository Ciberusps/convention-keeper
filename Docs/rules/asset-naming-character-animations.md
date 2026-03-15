# asset-naming-character-animations

Animations under `Content/{ProjectName}/Characters/{CharacterName}/Animations` must be named **AS_{CharacterName}_*** with an optional zero-padded number suffix (e.g. `AS_Zombie_Jump_01`).

## Rationale

- **AS_** matches the common “Animation Sequence” prefix.
- **{CharacterName}** ties the asset to the character folder and avoids collisions across characters.
- Zero-padded suffixes (e.g. `_01`) keep sort order correct and align with style guides.

## References

- [UE5 Style Guide – Asset Naming (1.1, 1.2)](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#1-asset-naming-conventions)
- [UE5 Style Guide – Animations (1.2.2)](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#122-animations)
