# folder-structure-character-gyms

For each resolved character, the folder `Content/{ProjectName}/Characters/{CharacterName}/Gyms/` must exist (see `folder-structure-character`) and must **directly** contain `.uasset` / `.umap` files whose **base names** (no extension), after placeholder substitution, are:

- `Gym_{CharacterName}`
- `AIGym_{CharacterName}`
- `AIGym_{CharacterName}_Arena`
- `AnimGym_{CharacterName}`

Example for `CharacterName = Zombie`: `Gym_Zombie`, `AIGym_Zombie`, `AIGym_Zombie_Arena`, `AnimGym_Zombie`.

Checks are **non-recursive** (only the `Gyms` directory, not subfolders). Validation runs only when the resolved directory equals the rule’s `FolderPath` (so parent `Characters/{CharacterName}/` is not scanned for gym asset names). Messages use the full `Content/.../AssetName` path (editor link → `/Game/...`).

## Base rule options

Implemented on `UConventionKeeperRule_FolderStructure`:

- **RequiredAssets** / **BannedAssets** — patterns with the same `{Placeholder}` syntax as paths.
- **Other Assets Not Allowed** (`bOtherAssetsNotAllowed`) — on the Earendil gym rule this is **true**: only the four required gym assets may exist in `Gyms/` (same idea as **Other Folders Not Allowed** for subfolders).
- **bValidateOnPerAssetSave** (default **true**) — when **false**, this rule is skipped for validation runs scoped to individual asset package paths (on-save / validate selection); full scans and explicit folder selection still run it.

## Rationale

Gym maps and related assets stay discoverable and consistent per character; validating on per-asset saves catches missing gyms when editing anything under that tree.
