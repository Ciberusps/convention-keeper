# asset-naming-texture

Имена **текстур** должны начинаться с префикса по типу. У текстур с префиксом **T_** суффикс (если есть) может состоять только из букв из списка стиля.

## Префикс по типу

| Тип | Префикс | Пример |
|-----|---------|--------|
| Texture 2D | **T_** | T_Bob_D, T_Rock_N, T_Noise_ERO |
| Texture Cube | **TC_** | TC_Sky, TC_Reflection |
| Media Texture | **MT_** | MT_Webcam |
| Render Target 2D | **RT_** | RT_SceneCapture |
| Cube Render Target | **RTC_** | RTC_Reflection |
| Texture Light Profile | **TLP_** | TLP_Soft |

## Суффикс для T_ (Texture 2D)

Если после базового имени идёт суффикс, он может содержать только буквы: **D, N, R, A, O, B, E, M, S** (одну или несколько). По гайду: _D (Diffuse/Albedo), _N (Normal), _R (Roughness), _A (Alpha), _O (Ambient Occlusion), _B (Bump), _E (Emissive), _M (Mask/Metallic), _S (Specular). Упакованные текстуры — несколько букв (напр. _ERO).

**Верно:** `T_Character_D`, `T_Rock_N`, `T_Noise_ERO`, `T_Material`, `TC_Sky`, `RT_Buffer`  
**Неверно:** `Character_D` (нет T_), `T_Character_X` (X не допускается), `Texture_Rock` (неверный префикс)

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются все типы текстур (Texture2D, TextureCube, Media Texture, Render Target, Cube Render Target, Texture Light Profile).

## Ссылки

- [UE5 Style Guide – 1.2.6 Textures](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#126-textures)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
