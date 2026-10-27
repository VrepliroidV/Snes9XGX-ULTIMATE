/****************************************************************************
 * Snes9x GX ULTIMATE
 *
 * menumusic.cpp
 *
 * Menu music: the OGG files of <APPFOLDER>/music (GCSettings.MenuMusic) and
 * the mini player of the menu. The file playing is read into the MEM2 heap
 * and looped by the OGG player. It plays in the menu before a game is
 * chosen: the in-game menu is silent, and the music goes on where it was
 * when the game is closed. The menu thread (settings) and the GUI thread
 * (player buttons) both use it, so everything here takes a lock.
 ***************************************************************************/

#include <gccore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ogc/lwp_watchdog.h>
#include <ogc/mutex.h>

#include "snes9xtx.h"
#include "menumusic.h"
#include "fileop.h"
#include "utils/bezel.h"
#include "utils/oggplayer.h"

#ifdef HW_RVL

#include "mem2.h"

#define MENU_MUSIC_MAX_SIZE (12 * 1024 * 1024) // MEM2 heap room (20 MB in all, ~6 MB in use)

static const int musicDevices[] = { DEVICE_SD, DEVICE_USB };

static mutex_t musicLock = LWP_MUTEX_NULL;
static char (*names)[BEZEL_NAME_MAX] = NULL; // the music folder
static int count = 0;
static int current = -1;      // the file of names[] that is chosen, -1: none
static u8 *oggData = NULL;    // that file, read
static u32 oggSize = 0;
static int loaded = -1;       // which file oggData holds
static int state = MUSIC_STOPPED;
static bool oggActive = false; // the OGG player plays oggData
static s32 resumeAt = 0;      // where to start again (ms) after a game ran
static bool inGame = false;    // the in-game menu: no music
static u32 changes = 0;

static void Lock()
{
	if(musicLock == LWP_MUTEX_NULL)
		LWP_MutexInit(&musicLock, true);
	LWP_MutexLock(musicLock);
}

static void Unlock()
{
	LWP_MutexUnlock(musicLock);
}

int MenuMusicList(char (*list)[BEZEL_NAME_MAX], int max)
{
	char dir[MAXPATHLEN];
	int n = 0;
	for (unsigned int i = 0; i < sizeof(musicDevices) / sizeof(musicDevices[0]); i++)
	{
		snprintf(dir, sizeof(dir), "%s%s", pathPrefix[musicDevices[i]], MENU_MUSIC_FOLDER);
		n = bezel_list_ext(dir, ".ogg", list, n, max);
	}
	return n;
}

static void Scan()
{
	if(!names)
		names = (char (*)[BEZEL_NAME_MAX]) malloc(MAX_MENU_MUSIC * BEZEL_NAME_MAX);
	count = names ? MenuMusicList(names, MAX_MENU_MUSIC) : 0;
	current = -1;
	loaded = -1; // the indexes may have changed
}

static void StopPlayer()
{
	if(oggActive)
	{
		StopOgg();
		oggActive = false;
	}
}

static bool Find(const char *name, char *path)
{
	struct stat st;
	for (unsigned int i = 0; i < sizeof(musicDevices) / sizeof(musicDevices[0]); i++)
	{
		snprintf(path, MAXPATHLEN, "%s%s/%s", pathPrefix[musicDevices[i]], MENU_MUSIC_FOLDER, name);
		if (stat(path, &st) == 0 && !S_ISDIR(st.st_mode))
			return true;
	}
	return false;
}

// Reads names[current] into oggData (the player must be stopped).
static bool Read()
{
	if(current < 0 || current >= count)
		return false;
	if(loaded == current && oggData)
		return true;

	if(oggData)
	{
		mem2_free(oggData);
		oggData = NULL;
		oggSize = 0;
	}
	loaded = -1;

	char path[MAXPATHLEN];
	if(!Find(names[current], path))
		return false;
	FILE *file = fopen(path, "rb");
	if(!file)
		return false;
	fseeko(file, 0, SEEK_END);
	size_t size = ftello(file);
	if(size == 0 || size > MENU_MUSIC_MAX_SIZE)
	{
		fclose(file);
		return false;
	}
	u8 *data = (u8 *)mem2_malloc(size);
	if(!data)
	{
		fclose(file);
		return false;
	}
	fseeko(file, 0, SEEK_SET);
	size_t got = fread(data, 1, size, file);
	fclose(file);
	if(got != size)
	{
		mem2_free(data);
		return false;
	}
	oggData = data;
	oggSize = size;
	loaded = current;
	return true;
}

static void Start(s32 at)
{
	StopPlayer();
	if(!Read())
	{
		state = MUSIC_STOPPED;
		return;
	}
	PlayOgg(oggData, oggSize, at, OGG_INFINITE_TIME);
	SetVolumeOgg(2.55f * GCSettings.MusicVolume);
	oggActive = true;
	state = MUSIC_PLAYING;
}

// The file of the setting: none, one by chance or the one named
static void Pick()
{
	current = -1;
	if(GCSettings.MenuMusic[0] == 0 || count == 0)
		return;
	if(strcmp(GCSettings.MenuMusic, MENU_MUSIC_RANDOM) == 0)
	{
		current = (int)(gettime() % count);
		return;
	}
	for(int i = 0; i < count; i++)
	{
		if(strcasecmp(names[i], GCSettings.MenuMusic) == 0)
		{
			current = i;
			return;
		}
	}
}

void MenuMusicInit()
{
	Lock();
	Scan();
	Pick();
	state = current >= 0 ? MUSIC_PLAYING : MUSIC_STOPPED;
	resumeAt = 0;
	changes++;
	Unlock();
}

void MenuMusicApplySetting()
{
	Lock();
	StopPlayer();
	Scan();
	Pick();
	resumeAt = 0;
	if(current < 0)
		state = MUSIC_STOPPED;
	else if(inGame)
		state = MUSIC_PLAYING; // once the game is closed
	else
		Start(0);
	changes++;
	Unlock();
}

void MenuMusicEnter(bool game)
{
	Lock();
	inGame = game;
	if(!inGame && state == MUSIC_PLAYING && !oggActive)
		Start(resumeAt);
	changes++;
	Unlock();
}

void MenuMusicLeave()
{
	Lock();
	if(oggActive)
	{
		s32 at = GetTimeOgg();
		resumeAt = at > 0 ? at : 0;
		StopPlayer();
	}
	Unlock();
}

void MenuMusicPlay()
{
	Lock();
	if(count > 0)
	{
		if(state == MUSIC_PAUSED && oggActive)
		{
			PauseOgg(0);
			state = MUSIC_PLAYING;
		}
		else if(state != MUSIC_PLAYING || !oggActive)
		{
			if(current < 0)
				current = 0;
			Start(resumeAt); // 0 unless paused while a game ran
		}
		changes++;
	}
	Unlock();
}

void MenuMusicPause()
{
	Lock();
	if(state == MUSIC_PLAYING)
	{
		if(oggActive)
		{
			PauseOgg(1);
			s32 at = GetTimeOgg();
			resumeAt = at > 0 ? at : 0;
		}
		state = MUSIC_PAUSED;
		changes++;
	}
	Unlock();
}

void MenuMusicStop()
{
	Lock();
	StopPlayer();
	resumeAt = 0;
	state = MUSIC_STOPPED;
	changes++;
	Unlock();
}

void MenuMusicSkip(int dir)
{
	Lock();
	if(count > 0)
	{
		StopPlayer();
		if(current < 0)
			current = dir > 0 ? 0 : count - 1;
		else
			current = (current + dir + count) % count;
		resumeAt = 0;
		Start(0);
		changes++;
	}
	Unlock();
}

void MenuMusicSetVolume(int volume)
{
	Lock();
	if(oggActive)
		SetVolumeOgg(2.55f * volume);
	Unlock();
}

int MenuMusicCount()
{
	return count;
}

int MenuMusicState()
{
	return state;
}

void MenuMusicName(char *out, int len)
{
	Lock();
	if(current >= 0 && current < count)
		bezel_display_name_ext(names[current], ".ogg", out, len);
	else
		out[0] = 0;
	Unlock();
}

u32 MenuMusicChanges()
{
	return changes;
}

#else // GameCube: no menu music

int MenuMusicList(char (*list)[128], int max) { return 0; }
void MenuMusicInit() {}
void MenuMusicApplySetting() {}
void MenuMusicEnter(bool game) {}
void MenuMusicLeave() {}
void MenuMusicPlay() {}
void MenuMusicPause() {}
void MenuMusicStop() {}
void MenuMusicSkip(int dir) {}
void MenuMusicSetVolume(int volume) {}
int MenuMusicCount() { return 0; }
int MenuMusicState() { return MUSIC_STOPPED; }
void MenuMusicName(char *out, int len) { out[0] = 0; }
u32 MenuMusicChanges() { return 0; }

#endif
