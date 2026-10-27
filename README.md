# Snes9x GX ULTIMATE

Emulador de Super Nintendo para Wii e GameCube, por VrepliroidV. É baseado no
[Snes9x TX 1.1.3](https://github.com/saulfabregwiivc/Snes9xTX) (Tanooki), que é
um fork do [Snes9x GX](https://github.com/dborth/snes9xgx) (Tantric), feito a
partir do [Snes9x](https://github.com/snes9xgit/snes9x).

Super Nintendo emulator for Wii and GameCube by VrepliroidV, based on Snes9x TX
1.1.3 (Tanooki), a fork of Snes9x GX (Tantric), built on Snes9x.

## Recursos / Features

- Molduras em PNG ao redor do jogo em 480i/480p, com a área transparente
  achada sozinha (molduras de 1920x1080 do RetroArch funcionam). Vem com uma
  moldura de TV por padrão. / PNG bezels in 480i/480p, the game fills the
  transparent window by itself; a TV frame is built in.
- Overclock automático da CPU do SNES. / Automatic CPU overclock.
- Configurações por jogo. / Per-game settings.
- Auto Crop das bordas pretas. / Auto Crop of black borders.
- Cheats Game Genie e Action Replay digitados no menu. / Cheats typed in the menu.
- Controles USB do tipo Xbox 360 (XInput) e receptores 2.4 GHz no Wii, até 4.
  / Xbox 360 (XInput) USB controllers and 2.4 GHz receivers, up to 4.
- Opção de região NTSC (Lie to PAL). / NTSC (Lie to PAL) region option.
- Música no menu: os `.ogg` da pasta `snes9xgxultimate/music`, escolhidos nas
  configurações, com um mini player (voltar, play, pause, stop, avançar). /
  Menu music from the OGG files of `snes9xgxultimate/music`, with a mini player.

## Instalação / Install

Extraia o `Snes9xGXUltimate-Wii.zip` da página de
[Releases](../../releases) na raiz do SD ou do pendrive. O emulador fica em
`apps/snes9xgxultimate` e as ROMs, saves, cheats e molduras em
`snes9xgxultimate/` (com a pasta `music` para as músicas do menu). Ele não mexe nas pastas do Snes9x TX nem do Snes9x GX.

Extract `Snes9xGXUltimate-Wii.zip` from [Releases](../../releases) to the root
of the SD card or USB drive. The app is in `apps/snes9xgxultimate`, its data in
`snes9xgxultimate/`.

Mais detalhes no [README.txt](README.txt). / More in [README.txt](README.txt).

## Compilar / Building

O GitHub Actions compila as versões de Wii e GameCube a cada push
(`.github/workflows/main.yml`), com o devkitPPC da imagem
`devkitpro/devkitppc:20230110`. Localmente: `make` com o devkitPPC e a libogc
instalados.

## Créditos / Credits

| | |
|---|---|
| Snes9x GX ULTIMATE | VrepliroidV |
| Snes9x TX | Tanooki |
| Menu artwork | the3seashells, Tanooki |
| Snes9x GX Wii | Tantric |
| Snes9x GX GameCube | SoftDev, crunchy2, Eke-Eke, others |
| Snes9x | Snes9x Team |
| libwiigui | Tantric |
| libogc / devkitPPC | shagkur & WinterMute |
| FreeTypeGX | Armin Tamzarian |

## Licença / License

O Snes9x tem a sua própria licença, só para uso não comercial (veja
[LICENSE](LICENSE)). O código do port para Wii/GameCube (Snes9x GX) é
distribuído sob a GNU GPL versão 2. O código das molduras
(`source/utils/bezel.c`) usa a licença zlib.

Snes9x has its own license, for non-commercial use only (see
[LICENSE](LICENSE)). The Wii/GameCube port (Snes9x GX) is distributed under
the GNU GPL version 2. The bezel code (`source/utils/bezel.c`) is under the
zlib license.
