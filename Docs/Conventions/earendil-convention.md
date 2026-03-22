# Earendil convention

**Name (doc slug):** `earendil-convention`  
**Engine class:** `UEarendilConvention`

## Summary

Default game preset for Convention Keeper: extends **UE5 Style Guide** and adds **Earendil-specific** folder structure and a few naming overrides. Upstream style guide remains the reference for most asset types.

## Base convention

All rules from [`ue5-style-guide-convention`](./ue5-style-guide-convention.md) apply unless disabled or replaced below.

- **Base documentation:** same repo, path `Docs/Conventions/ue5-style-guide-convention.md`
- **Upstream UE5 Style Guide:** [Allar v2](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file)

## Rules defined on this convention (not inherited as-is)

### Folder structure

| RuleId | Purpose |
|--------|---------|
| `folder-structure-content` | Expected layout under `Content/{ProjectName}/` |
| `folder-structure-project-name` | Project root folder naming |
| `folder-structure-character` | Character-related paths |
| `folder-structure-core-ai` | Core AI paths |

See `Docs/Rules/{RuleId}.md` for each.

### Asset naming overrides / additions

| RuleId | Note |
|--------|------|
| `asset-naming-anim-sequence` | **Replaced** (RuleOverrides): implementation uses rule id `ec-asset-naming-anim-sequence`, prefix **`AS_`** instead of base `A_` |
| `asset-naming-character-animations` | Character animation naming |
| `ec-asset-naming-state-tree` | StateTree asset naming |

### Rule override mechanism

`asset-naming-anim-sequence` is wired via **RuleOverrides** → `Replace` on the base rule id. Other additions live in the convention’s **Rules** array.

## Customizing for your project

Duplicate or subclass the convention asset, adjust `Rules` / `RuleOverrides`, and point **Convention Documentation Id** (or doc path override) at your fork’s `Docs/Conventions/` if you publish custom markdown.
