// Convention Keeper (default) rule descriptions — Russian.

{ FName(TEXT("folder-structure-content")), TEXT("В корне Content должны быть папки: 3rdParty, {ProjectName}, FMOD, Movies.") },
{ FName(TEXT("folder-structure-project-name")), TEXT("В Content/{ProjectName}/ обязательны папки: Characters, Maps, Core, SFX, VFX, AI.") },
{ FName(TEXT("folder-structure-character")), TEXT("В каждой папке персонажа должны быть: AI, Projectiles, Animations, Gyms, Data, Abilities, Materials.") },
{ FName(TEXT("folder-structure-character-gyms")), TEXT("В Content/{ProjectName}/Characters/{CharacterName}/Gyms/ только Gym_{CharacterName}, AIGym_{CharacterName}, AIGym_{CharacterName}_Arena, AnimGym_{CharacterName} (.uasset/.umap); других ассетов в этой папке быть не должно.") },
{ FName(TEXT("folder-structure-core-ai")), TEXT("Папка Content/{ProjectName}/Core/AI/ должна существовать.") },
{ FName(TEXT("ec-asset-naming-anim-sequence")), TEXT("Ассеты Animation Sequence должны иметь префикс AS_ (EarendilConvention).") },
{ FName(TEXT("ec-asset-naming-state-tree")), TEXT("Ассеты StateTree должны иметь префикс ST_ (EarendilConvention).") },
{ FName(TEXT("asset-naming-character-animations")), TEXT("Анимации в Content/{ProjectName}/Characters/{CharacterName}/Animations должны называться AS_{CharacterName}_* с опциональным нулевым суффиксом (напр. AS_Zombie_Jump_01).") },
