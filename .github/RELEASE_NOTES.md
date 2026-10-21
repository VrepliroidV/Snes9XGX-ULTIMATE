Versão modificada do [Snes9x TX 1.1.3](https://github.com/saulfabregwiivc/Snes9xTX) (Tanooki) para Wii, com suporte a controles USB sem fio, Auto Crop, overclock automático, configurações por jogo e cheats digitados no menu. *English below.*

## Novidades desta versão

**Overclock automático** (Configurações > Emulação Hacks > CPU Overclocking > **Automático**):
- O overclock só entra quando o jogo fica lento, um nível por vez (Baixo, Médio, Máximo), e volta a descer quando a cena alivia. O emulador mede, a cada quadro, quanto tempo a CPU do console passa esperando.
- Fica desligado nas transições: tela apagada ou escurecendo, carregamentos e envio de música para o chip de som, que é quando jogos como **Top Gear** e **Primal Rage** travavam ou ficavam com a tela preta em Max. Cada jogo começa sem overclock, então os jogos que não abrem com overclock abrem normalmente.
- Com **Mostrar FPS** ligado, aparece o nível em uso e quanto do quadro a CPU passou trabalhando, por exemplo `OC Med 72%`.

**Configurações por jogo** (Configurações > botão **Por Jogo**): guarda as opções de vídeo, som e emulação só para o jogo aberto, no arquivo `<jogo>.cfg` junto dos saves. Por exemplo, um jogo com Auto Crop e outro com overclock fixo. Desligar o botão faz o jogo voltar às configurações gerais.

**Auto Crop** (Game Settings > Video > Auto Crop): corta as bordas pretas ao redor da imagem do jogo, com as mesmas regras do núcleo [snes9x-ntsc-lie-pal](https://github.com/VrepliroidV/snes9x-ntsc-lie-pal).
- **Off**, **Fit** (amplia sem deformar os pixels) ou **Stretch** (estica até preencher o quadro).
- Linhas desenhadas com a tela desligada são cortadas em 2 quadros. Barras de tiles pretos só são cortadas quando a tela parece gameplay, então telas de logo e texto sobre fundo preto ficam inteiras.
- Enquadramentos que ficam 5 segundos na tela são memorizados para o jogo, no arquivo `<jogo>.autocrop` junto dos saves. Apague o arquivo para o jogo aprender de novo.
- Gráficos que aparecem na área cortada voltam a aparecer no mesmo quadro. A mira da Super Scope e o mouse acompanham o corte.
- **Auto Crop Scaling**: **Suave** preenche a tela e fica nítido mesmo com o filtro bilinear desligado. **Inteira** amplia só em número inteiro, sem nenhuma linha misturada; em 240p, num jogo com faixas em cima e embaixo, a altura fica como está.

**Cheats digitados no menu** (Game Settings > Cheats), sem precisar copiar arquivo para o SD:
- **Adicionar Código**: escolha Game Genie ou Action Replay e digite só as letras e os números. O `-`, o `:` e o `+` entre vários códigos entram sozinhos. Depois, dê um nome ao código.
- Clique num código para ligar ou desligar. **Renomear Código** troca o nome e **Apagar Código** remove um.
- Tudo é salvo no arquivo de cheats do jogo (`snes9xtx/cheats/<jogo>.cht`), com o estado ligado ou desligado. Os códigos ligados voltam a funcionar quando o jogo abre.
- Funciona com qualquer controle, inclusive os controles USB, e o direcional chega até o botão Voltar.

**Atalhos do menu**
- Os atalhos L + R + Start (controle de GameCube) e L + R + Plus (Classic Controller) foram retirados: eles atrapalhavam em jogos e cheats.
- Agora o menu abre com **L + Select + Start** nos controles USB, **Home** no Wiimote e no Classic Controller, e o **direcional C para a esquerda** no controle de GameCube.

Textos novos traduzidos para português.

## O que já vinha na versão anterior

- **Controles USB do tipo Xbox 360 (XInput)**, com fio ou com receptor 2.4 GHz plugado direto no USB do Wii. Testado com o **Retroflag Classic Controller-M wireless** (estilo Mega Drive) e com um **controle sem fio genérico de SNES Classic Mini**. Até 4 controles; o primeiro receptor plugado é o jogador 1. Pode plugar e tirar com o emulador aberto. O emulador vê esses controles como **controle de GameCube**.
- **Região** aplicada em todo jogo carregado, e a opção **NTSC (Lie to PAL)**: temporização NTSC (60 Hz), mas o jogo acredita que está num console PAL.
- Música do menu: `bg_music.ogg` na pasta do app, em `sd:/snes9xtx` ou em `usb:/snes9xtx`.
- Correção do erro de exceção ao abrir o emulador com alguns receptores USB plugados junto com outro aparelho USB.

## Instalação

1. Baixe o `Snes9xTX-Wii.zip` e extraia na raiz do cartão SD ou do pendrive. Ele cria `apps/snes9xtx` (o emulador) e a pasta `snes9xtx` com `roms`, `saves` e `cheats`.
2. Se você já tem o Snes9x TX instalado, basta trocar o `boot.dol` da pasta `apps/snes9xtx`. Suas configurações e saves continuam.

O `Snes9xTX-GameCube.zip` traz a versão de GameCube: tem o Auto Crop, o overclock automático, as configurações por jogo, os cheats e as melhorias de região, mas não os controles USB.

## Observações

- Plugue o receptor **direto no USB do Wii**. Ligado num adaptador na entrada do Wiimote, ele não funciona e pode travar o Wii.
- Funciona junto com um HD externo plugado na outra porta USB.

---

## English

Snes9x TX 1.1.3 for Wii with Xbox 360 (XInput) USB controllers, Auto Crop, automatic overclock, per-game settings and cheats typed in the menu.

New in this version:
- **Automatic CPU overclock** (Game Settings > Emulation Hacks > CPU Overclocking > Auto): the overclock goes up one level at a time (Low, Medium, Max) only when the game slows down, and back down when it is not needed. It stays off while the screen is dark or fading, while loading and while music goes to the sound chip (where Top Gear and Primal Rage hung at Max), and each game starts without it. With Show Frame Rate on, the level in use and how busy the CPU was are shown (e.g. `OC Med 72%`).
- **Per-game settings** (Game Settings > Per-Game): the video, audio and emulation options are kept for the loaded game only, in `<game>.cfg` next to the saves.
- **Auto Crop** (Game Settings > Video): crops black borders, with the rules of the snes9x-ntsc-lie-pal Libretro core. Off, Fit (keeps the pixel shape) or Stretch (fills the frame). Layouts seen for 5 seconds are remembered per game in `<game>.autocrop` next to the saves. **Auto Crop Scaling**: Smooth fills the frame and stays sharp with bilinear filtering off; Integer only scales by whole numbers.
- **Cheats** (Game Settings > Cheats): Add Code types Game Genie or Action Replay codes with the `-`, `:` and `+` added by themselves, then a name for the code; click a code to turn it on or off; Rename Code and Delete Code. Everything is saved to the game's cheat file, and codes saved as on are active when the game loads. Works with every controller.
- The L + R + Start (GameCube) and L + R + Plus (Classic Controller) menu combos were removed. The menu opens with L + Select + Start on USB pads, Home on Wii controllers and C stick left on GameCube controllers.

Already in the previous version: USB controllers read as GameCube controllers (tested with the Retroflag Classic Controller-M wireless and a generic SNES Classic Mini wireless pad, up to 4, hot-plug), the region option applied on every game load, the NTSC (Lie to PAL) region, menu music from `bg_music.ogg`, and a fix for a start-up crash with some USB receivers.

Install: extract `Snes9xTX-Wii.zip` to the root of the SD card or USB drive, or replace `apps/snes9xtx/boot.dol` in an existing install.

---

Snes9x TX is a fork of [Snes9x GX](https://github.com/dborth/snes9xgx), based on [Snes9x](https://github.com/snes9xgit/snes9x). Licensed under the GPL (see LICENSE, also in the .zip); the source code of this build is in the "Source code" files of this release.
