# asset-naming-level-map

**Level / Map** (World) assets may have no suffix or one of: **_P** (Persistent), **_Audio**, **_Lighting**, **_Geo**, **_Gameplay**.

**Valid:** `MainLevel`, `Campaign_P`, `Arena_Audio`, `Dungeon_Lighting`, `Hub_Geo`, `Battle_Gameplay`  
**Invalid:** `Level_Foo`, `Map_Other`, `Stage_01` (custom suffixes not in the allowed list)

Applies to assets under `Content/{ProjectName}/Maps`. Only `World` assets are checked. Level/Map files should be placed in a folder named Maps (see [2.4 Maps](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#24-all-map-files-belong-in-a-folder-called-maps)).

## Rationale

The [UE5 Style Guide 1.2.1 Most Common](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#121-most-common) specifies optional suffixes for sub-level types (Persistent, Audio, Lighting, Geometry, Gameplay) so level purpose is clear from the name.

## References

- [UE5 Style Guide – 1.2.1 Most Common](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#121-most-common)
- [UE5 Style Guide – 2.4 Maps](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#24-all-map-files-belong-in-a-folder-called-maps)
