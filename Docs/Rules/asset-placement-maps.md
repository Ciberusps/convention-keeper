# asset-placement-maps

**Level / Map** (World) assets must be located in a folder named **Maps**.

**Valid path:** `Content/{ProjectName}/Maps/MainLevel`, `Content/{ProjectName}/Maps/Campaign1/Arena_01`  
**Invalid path:** `Content/{ProjectName}/Levels/MainLevel`, `Content/{ProjectName}/Art/TestMap`

Applies to all World assets under `Content/{ProjectName}`. Naming of map assets is enforced separately by the [asset-naming-level-map](asset-naming-level-map.md) rule.

## Rationale

The [UE5 Style Guide 2.4](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#24-all-map-files-belong-in-a-folder-called-maps) states that all map files belong in a folder called Maps. This simplifies cooking, lighting scripts, and QA; it also makes it easy to tell someone where to find a map.

## References

- [UE5 Style Guide – 2.4 All Map Files Belong In A Folder Called Maps](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#24-all-map-files-belong-in-a-folder-called-maps)
- [UE5 Style Guide – 2. Content Directory Structure](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#2-content-directory-structure)
