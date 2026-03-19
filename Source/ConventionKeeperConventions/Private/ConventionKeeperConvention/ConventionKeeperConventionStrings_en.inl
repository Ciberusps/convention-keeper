// Convention Keeper (default) rule descriptions — English.

{ FName(TEXT("folder-structure-content")), TEXT("Root Content folder must contain 3rdParty, {ProjectName}, FMOD, Movies.") },
{ FName(TEXT("folder-structure-project-name")), TEXT("Under Content/{ProjectName}/ require Characters, Maps, Core, SFX, VFX, AI.") },
{ FName(TEXT("folder-structure-character")), TEXT("Each character folder must have AI, Projectiles, Animations, Gyms, Data, Abilities, Materials.") },
{ FName(TEXT("folder-structure-core-ai")), TEXT("Content/{ProjectName}/Core/AI/ must exist.") },
{ FName(TEXT("ck-asset-naming-anim-sequence")), TEXT("Animation Sequence assets must use prefix AS_ (CKConvention).") },
{ FName(TEXT("ck-asset-naming-state-tree")), TEXT("StateTree assets must use prefix ST_ (CKConvention).") },
{ FName(TEXT("asset-naming-character-animations")), TEXT("Animations in Content/{ProjectName}/Characters/{CharacterName}/Animations must be named AS_{CharacterName}_* with optional zero-padded number suffix (e.g. AS_Zombie_Jump_01).") },
