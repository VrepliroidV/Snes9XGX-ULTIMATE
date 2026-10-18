Versão modificada do [Snes9x TX 1.1.3](https://github.com/saulfabregwiivc/Snes9xTX) (Tanooki) para Wii, com suporte a controles USB sem fio. *English below.*

## O que tem de novo

**Controles USB do tipo Xbox 360 (XInput)**, com fio ou com receptor 2.4 GHz plugado direto no USB do Wii.
- Testado com o **Retroflag Classic Controller-M wireless** (estilo Mega Drive) e com um **controle sem fio genérico de SNES Classic Mini**. Outros controles que se apresentam como controle de Xbox 360 devem funcionar também.
- Até 4 controles ao mesmo tempo. O primeiro receptor plugado é o jogador 1, o segundo é o jogador 2.
- Pode plugar e tirar o receptor com o emulador aberto.
- O emulador enxerga esses controles como **controle de GameCube**. Para mudar os botões, configure o controle de GameCube.
- **L + Select + Start** abre o menu do emulador, já que esses controles não têm botão Home.

**Região**
- A região escolhida nas opções agora vale para todo jogo carregado. Antes ela só era aplicada a partir da segunda vez que se abria um jogo.
- Nova opção **NTSC (Lie to PAL)**: o jogo roda com a temporização NTSC (60 Hz), mas acredita que está num console PAL. Serve para jogos PAL que travam, mostram aviso ou ficam com a tela preta quando percebem a troca de região.

**Correções**
- Música do menu: o emulador procura o `bg_music.ogg` na pasta do app (`apps/snes9xtx`), em `sd:/snes9xtx` e em `usb:/snes9xtx`.
- O suporte a controle de PS3 (DualShock 3) mandava comandos inválidos para o sistema do Wii quando havia outro aparelho USB do tipo HID plugado. Com alguns receptores, isso dava erro de exceção ao abrir o emulador.

## Instalação

1. Baixe o `Snes9xTX-Wii.zip` e extraia na raiz do cartão SD ou do pendrive. Ele cria as pastas `apps/snes9xtx` (o emulador) e `snes9xtx` (com `roms`, `saves` e `cheats`).
2. Se você já tem o Snes9x TX instalado, basta trocar o `boot.dol` da pasta `apps/snes9xtx`. Suas configurações e saves continuam.
3. Música do menu (opcional): coloque um arquivo `bg_music.ogg` na pasta `apps/snes9xtx`.

O `Snes9xTX-GameCube.zip` traz a versão de GameCube. Ela tem as melhorias de região, mas não os controles USB, porque o GameCube não tem USB.

## Observações

- Plugue o receptor **direto no USB do Wii**. Ligado num adaptador na entrada do Wiimote, ele não funciona e pode travar o Wii.
- Funciona junto com um HD externo plugado na outra porta USB.

---

## English

Snes9x TX 1.1.3 for Wii with support for **Xbox 360 (XInput) USB controllers**, wired or through a 2.4 GHz receiver plugged straight into the Wii.

- Tested with the Retroflag Classic Controller-M wireless and a generic SNES Classic Mini wireless pad. Up to 4 at once; the first receiver plugged in is player 1. Hot-plug works.
- They show up as **GameCube controllers**, so remap them through the GameCube controller settings.
- **L + Select + Start** opens the menu.
- The region option now applies to every game loaded, and there is a new **NTSC (Lie to PAL)** region: NTSC timing, but the game sees a PAL console.
- Menu music is read from `bg_music.ogg` in `apps/snes9xtx`, `sd:/snes9xtx` or `usb:/snes9xtx`.
- Fixed: the DualShock 3 support sent requests to an invalid handle whenever another USB HID device was plugged in, which crashed the emulator at start-up with some receivers.

Install: extract `Snes9xTX-Wii.zip` to the root of the SD card or USB drive, or replace `apps/snes9xtx/boot.dol` in an existing install.

---

Snes9x TX is a fork of [Snes9x GX](https://github.com/dborth/snes9xgx), based on [Snes9x](https://github.com/snes9xgit/snes9x). Licensed under the GPL (see LICENSE, also in the .zip); the source code of this build is in the "Source code" files of this release.
