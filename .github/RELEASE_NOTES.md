**Snes9x GX ULTIMATE 1.0.0**: emulador de Super Nintendo para Wii, baseado no [Snes9x TX 1.1.3](https://github.com/saulfabregwiivc/Snes9xTX) (Tanooki), que é um fork do [Snes9x GX](https://github.com/dborth/snes9xgx) (Tantric). *English below.*

## Recursos

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

1. Baixe o `Snes9xGXUltimate-Wii.zip` e extraia na raiz do cartão SD ou do pendrive. Ele cria `apps/snes9xgxultimate` (o emulador) e a pasta `snes9xgxultimate` com `roms`, `saves`, `cheats` e `bezels`.
2. É um app separado: pode ficar instalado junto com o Snes9x TX ou o Snes9x GX, e não mexe nas pastas deles. Para usar seus saves antigos, copie os arquivos de `snes9xtx/saves` (ou `snes9x/saves`) para `snes9xgxultimate/saves`. As ROMs podem ser copiadas para `snes9xgxultimate/roms`, ou escolha outra pasta em Settings > Saving & Loading.

O `Snes9xGXUltimate-GameCube.zip` traz a versão de GameCube: tem as molduras, o Auto Crop, o overclock automático, as configurações por jogo, os cheats e as melhorias de região, mas não os controles USB.

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

**Snes9x GX ULTIMATE 1.0.0**: Super Nintendo emulator for Wii, based on Snes9x TX 1.1.3 (Tanooki), a fork of Snes9x GX (Tantric).

- **PNG bezels** (Game Settings > Video > Bezel), in 480i and 480p (not in 240p). The transparent window in the middle of the PNG is found by itself and the game fills it, with the bezel drawn over its edges; a PNG without a window is a background behind the game. Any PNG size works (1920x1080 RetroArch bezels included). Choices: Off, Default (TV) (the TV frame built into the emulator, on by default), Auto (`<game>.png`, else `default.png`, else the TV frame) and each PNG in `snes9xgxultimate/bezels` on the SD card or USB drive. Kept per game too.
- Automatic CPU overclock, per-game settings, Auto Crop of black borders, cheats typed in the menu, Xbox 360 (XInput) USB controllers and 2.4 GHz receivers read as GameCube controllers (up to 4, L + Select + Start opens the menu), the region option and NTSC (Lie to PAL).

Install: extract `Snes9xGXUltimate-Wii.zip` to the root of the SD card or USB drive. It is a separate app (`apps/snes9xgxultimate`) with its own data folder (`snes9xgxultimate`), so it can sit next to Snes9x TX or Snes9x GX; copy your saves from `snes9xtx/saves` if you want to keep them.

---

Snes9x GX ULTIMATE is based on [Snes9x TX](https://github.com/saulfabregwiivc/Snes9xTX), a fork of [Snes9x GX](https://github.com/dborth/snes9xgx), based on [Snes9x](https://github.com/snes9xgit/snes9x). Snes9x is under its own non-commercial license (LICENSE, also in the .zip) and the Wii/GameCube port under the GPL version 2; the source code of this build is in the "Source code" files of this release.
