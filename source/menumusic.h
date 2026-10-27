/****************************************************************************
 * Snes9x GX ULTIMATE
 *
 * menumusic.h
 *
 * Menu music: the OGG files of <APPFOLDER>/music (GCSettings.MenuMusic) and
 * the mini player of the menu
 ***************************************************************************/

#ifndef _MENUMUSIC_H_
#define _MENUMUSIC_H_

#include <gctypes.h>

#define MAX_MENU_MUSIC 512

enum
{
	MUSIC_STOPPED,
	MUSIC_PLAYING,
	MUSIC_PAUSED
};

// The OGG files of the music folder (SD card, then USB drive), sorted.
// names: room for max names of BEZEL_NAME_MAX (128) characters.
int MenuMusicList(char (*names)[128], int max);

void MenuMusicInit();         // once the settings are loaded: picks the music of the setting
void MenuMusicApplySetting(); // the setting changed: plays its music from the start
void MenuMusicEnter();        // the menu opens: plays again if it was playing
void MenuMusicLeave();        // the game runs: stops, remembering the position
void MenuMusicTick();         // every frame of the menu (GUI thread)

// the mini player
void MenuMusicPlay();
void MenuMusicPause();
void MenuMusicStop();
void MenuMusicSkip(int dir);  // next (1) or previous (-1) file of the folder
void MenuMusicSetVolume(int volume); // 0 - 100

int MenuMusicCount();         // files in the music folder
int MenuMusicState();
void MenuMusicName(char *out, int len); // the current file without ".ogg", "" for none
u32 MenuMusicChanges();       // changes whenever the state or the file changes

#endif
