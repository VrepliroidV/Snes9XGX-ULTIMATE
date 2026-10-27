**Snes9x GX ULTIMATE 1.1.2**: emulador de Super Nintendo para Wii, baseado no [Snes9x TX 1.1.3](https://github.com/saulfabregwiivc/Snes9xTX) (Tanooki), que é um fork do [Snes9x GX](https://github.com/dborth/snes9xgx) (Tantric). *English below.*

## Novidades da 1.1.2

- A música não recomeça mais ao apertar um botão do menu com o controle (direcional e A), como o Settings: o mini player também andava com o direcional, e o botão de voltar ou avançar dele era apertado junto. Com uma música só na pasta, ela voltava para o início.

## Novidades da 1.1.1

- A música e o mini player ficam só no menu antes de escolher o jogo. O menu do jogo (Home) fica em silêncio, e a música volta a tocar do início quando você fecha o jogo (Menu Principal > Sair do Jogo).
- A música não recomeça mais do início ao mexer em alguns menus.
- Mudar o volume dos efeitos sonoros não muda mais o volume da música.

## Música no menu (1.1.0)

- **Pasta de músicas**: coloque arquivos `.ogg` em `snes9xgxultimate/music`, no SD ou no pendrive. Quantas músicas quiser, com qualquer nome, de até 12 MB cada (uns 10 minutos em 160 kbps).
- **Settings > Menu > Música do Menu**: **Sem Música**, **Aleatória** (sorteia uma música da pasta cada vez que o emulador abre, o padrão) ou cada música da pasta pelo nome. Ao trocar, a música nova já começa a tocar.
- **Mini player** embaixo da tela, abaixo dos botões do menu: voltar, play, pause, stop, avançar e o nome da música (nomes longos rolam). Ele funciona com o ponteiro do Wiimote, não muda a navegação pelo direcional e só aparece quando a pasta tem músicas. Voltar e avançar passam pelas músicas da pasta em ordem.
- O nome fica cinza com a música pausada ou parada.
- O `bg_music.ogg` na pasta do app não é mais usado: coloque a música na pasta `music`.

## O que já vinha na 1.0.0

- **Molduras em PNG** (Game Settings > Video > **Moldura**), para preencher o espaço vazio ao redor do jogo numa TV LCD:
  - Aparecem nos modos 480i e 480p (Rendering **Default**). Em 240p (Original) a imagem fica como sempre, sem moldura.
  - O emulador acha sozinho a área transparente no meio do PNG e encaixa a tela do jogo nela. A moldura é desenhada por cima, então cantos arredondados ficam certinhos. O Auto Crop continua funcionando dentro da moldura.
  - Um PNG sem área transparente no meio vira fundo, com o jogo na frente no tamanho de sempre.
  - PNG de qualquer tamanho, por exemplo os de 1920x1080 feitos para o RetroArch. Com o Wii em 16:9, use molduras de 16:9.
  - Opções: **Desligado**, **Padrão (TV)** (a moldura de TV que já vem no emulador, ligada por padrão), **Automática** (`<nome do jogo>.png`, senão `default.png`, senão a moldura de TV) e cada PNG da pasta `snes9xgxultimate/bezels`, no SD ou no pendrive. A escolha também entra nas configurações por jogo.
- **Overclock automático** (Emulation Hacks > CPU Overclocking > Automático): o overclock só entra quando o jogo fica lento e fica desligado nas transições, onde jogos como Top Gear e Primal Rage travavam em Max.
- **Configurações por jogo** (botão **Por Jogo**), no arquivo `<jogo>.cfg` junto dos saves.
- **Auto Crop** das bordas pretas (Video > Auto Crop: Fit ou Stretch) e **Auto Crop Scaling** (Suave ou Inteira).
- **Cheats digitados no menu** (Game Genie e Action Replay), com nome, renomear e apagar.
- **Controles USB do tipo Xbox 360 (XInput)**, com fio ou com receptor 2.4 GHz plugado direto no USB do Wii. Até 4 controles, vistos como controle de GameCube. O menu abre com **L + Select + Start**.
- **Região** aplicada em todo jogo, e a opção **NTSC (Lie to PAL)**.

## Instalação

1. Baixe o `Snes9xGXUltimate-Wii.zip` e extraia na raiz do cartão SD ou do pendrive. Ele cria `apps/snes9xgxultimate` (o emulador) e a pasta `snes9xgxultimate` com `roms`, `saves`, `cheats`, `bezels` e `music`. Quem já tem a 1.0.0 pode extrair por cima: as configurações e os saves continuam.
2. É um app separado: pode ficar instalado junto com o Snes9x TX ou o Snes9x GX, e não mexe nas pastas deles. Para usar seus saves antigos, copie os arquivos de `snes9xtx/saves` (ou `snes9x/saves`) para `snes9xgxultimate/saves`. As ROMs podem ser copiadas para `snes9xgxultimate/roms`, ou escolha outra pasta em Settings > Saving & Loading.

O `Snes9xGXUltimate-GameCube.zip` traz a versão de GameCube: tem as molduras, o Auto Crop, o overclock automático, as configurações por jogo, os cheats e as melhorias de região, mas não os controles USB nem a música do menu.

## Observações

- Plugue o receptor USB **direto no USB do Wii**. Ligado num adaptador na entrada do Wiimote, ele não funciona e pode travar o Wii.
- Funciona junto com um HD externo plugado na outra porta USB.

## Créditos

- Snes9x GX ULTIMATE: VrepliroidV
- Snes9x TX: Tanooki
- Snes9x GX: Tantric, e no GameCube SoftDev, crunchy2, Eke-Eke e outros
- Snes9x: Snes9x Team

---

## English

**Snes9x GX ULTIMATE 1.1.2**: Super Nintendo emulator for Wii, based on Snes9x TX 1.1.3 (Tanooki), a fork of Snes9x GX (Tantric).

New in 1.1.2: the music no longer starts again when a menu button is pressed with the controller (the mini player took the d-pad too, and its previous or next button was pressed with the button of the menu).

New in 1.1.1: the menu music and its player are in the menu before a game is chosen only (the in-game menu is silent; the music starts again from the beginning when the game is closed); the music no longer starts again in some menus; the sound effects volume no longer changes the music volume.

Menu music (1.1.0):
- OGG files in `snes9xgxultimate/music` (SD card or USB drive), any number, up to 12 MB each.
- Settings > Menu > Menu Music: No Music, Random (one file of the folder at every start, the default) or one of the files; changing it plays the music at once.
- A mini player at the bottom of the menus, under the buttons: previous, play, pause, stop, next and the name of the music. It is used with the Wii remote pointer and is shown when the folder has music.
- `bg_music.ogg` in the app folder is not played any more: put the music in the music folder.

Already in 1.0.0:

- **PNG bezels** (Game Settings > Video > Bezel), in 480i and 480p (not in 240p). The transparent window in the middle of the PNG is found by itself and the game fills it, with the bezel drawn over its edges; a PNG without a window is a background behind the game. Any PNG size works (1920x1080 RetroArch bezels included). Choices: Off, Default (TV) (the TV frame built into the emulator, on by default), Auto (`<game>.png`, else `default.png`, else the TV frame) and each PNG in `snes9xgxultimate/bezels` on the SD card or USB drive. Kept per game too.
- Automatic CPU overclock, per-game settings, Auto Crop of black borders, cheats typed in the menu, Xbox 360 (XInput) USB controllers and 2.4 GHz receivers read as GameCube controllers (up to 4, L + Select + Start opens the menu), the region option and NTSC (Lie to PAL).

Install: extract `Snes9xGXUltimate-Wii.zip` to the root of the SD card or USB drive (over 1.0.0 too: settings and saves stay). It is a separate app (`apps/snes9xgxultimate`) with its own data folder (`snes9xgxultimate`), so it can sit next to Snes9x TX or Snes9x GX; copy your saves from `snes9xtx/saves` if you want to keep them.

---

Snes9x GX ULTIMATE is based on [Snes9x TX](https://github.com/saulfabregwiivc/Snes9xTX), a fork of [Snes9x GX](https://github.com/dborth/snes9xgx), based on [Snes9x](https://github.com/snes9xgit/snes9x). Snes9x is under its own non-commercial license (LICENSE, also in the .zip) and the Wii/GameCube port under the GPL version 2; the source code of this build is in the "Source code" files of this release.
