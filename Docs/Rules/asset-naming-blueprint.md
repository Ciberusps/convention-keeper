# asset-naming-blueprint

**Blueprint** and **Tutorial Blueprint** assets must use the prefix **BP_** or **TBP_**.

**Valid:** `BP_PlayerCharacter`, `BP_Barrel`, `TBP_IntroSequence`  
**Invalid:** `PlayerCharacter`, `MyBlueprint`, `Tutorial_Intro`

Applies to assets under `Content/{ProjectName}`. Does not apply to Blueprint Function Library (BPFL_), Blueprint Interface (BPI_), Blueprint Macro Library (BPML_), Blueprint Component (BP_*Component), AI Controller (AIC_), Behavior Tree types (BT*, EQS*), or Widget Blueprint (WBP_).

## Rationale

The [UE5 Style Guide 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints) uses BP_ for blueprints and TBP_ for tutorial blueprints so they sort and are clearly identifiable.

## References

- [UE5 Style Guide – 1.2.4 Blueprints](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#124-blueprints)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
