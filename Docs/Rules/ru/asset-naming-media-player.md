# asset-naming-media-player

Ассеты **Media Player** должны иметь префикс **MP_**.

**Верно:** `MP_StreamingVideo`, `MP_IntroCinematic`, `MP_BackgroundMusic`  
**Неверно:** `StreamingVideo`, `MediaPlayer_Intro`, `MyPlayer`

Правило действует для ассетов в `Content/{ProjectName}`. Проверяются только ассеты типа MediaPlayer.

## Зачем

В [UE5 Style Guide 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous) для Media Player задан префикс MP_, чтобы их можно было отличить от других медиа-ассетов.

## Ссылки

- [UE5 Style Guide – 1.2.7 Miscellaneous](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#127-miscellaneous)
- [UE5 Style Guide – 1.1 Base Asset Name](https://github.com/Allar/ue5-style-guide/tree/v2?tab=readme-ov-file#11-base-asset-name---prefix_baseassetname_variant_suffix)
