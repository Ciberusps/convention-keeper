# UE5 Style Guide convention

**Name (doc slug):** `ue5-style-guide-convention`  
**Engine class:** `UUE5StyleGuideConvention`

## Summary

Root preset for Convention Keeper: **PascalCase** for folders/assets where applicable, plus a large set of **asset naming** rules (prefixes/suffixes) and **placement** rules aligned with [Gamemakin / Allar UE5 Style Guide v2](https://github.com/Allar/ue5-style-guide/tree/v2).

## External reference

The upstream guide is the normative reference for naming philosophy and examples:

- [UE5 Style Guide v2 (README)](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file)

## Rules in this convention

Each check is a separate rule with a stable **RuleId** and a markdown page under `Docs/Rules/{RuleId}.md` (and `Docs/Rules/ru/` for Russian where present).

Includes, in brief:

- **Naming:** `naming-convention-pascalcase`
- **Asset naming:** one rule per major asset type (e.g. `asset-naming-texture`, `asset-naming-blueprint`, `asset-naming-static-mesh`, …) — see the `Docs/Rules/` directory for the full list.
- **Placement:** e.g. `asset-placement-maps`, `asset-placement-sound-class`

## Extending

Project conventions usually **extend** this class (or a preset that extends it) via `ExtendsConvention` / `ExtendsConventionAsset`, then add or override rules. Inherited rules are documented on the **base** convention page; only **new** or **overridden** rule ids belong in the derived convention doc.
