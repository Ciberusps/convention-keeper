# folder-structure-content

Root Content folder must contain: **3rdParty**, **{ProjectName}**, **FMOD**, **Movies**, **Developers**, **Splash**.

## Rationale

A single top-level structure under `Content/` avoids clutter and makes migrations and filtering predictable. Project-specific assets live under `{ProjectName}`; third-party and engine-level content stay separated.

## References

- [UE5 Style Guide – Directory Structure](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#2-content-directory-structure)
