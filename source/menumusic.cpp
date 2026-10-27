/****************************************************************************
 * Snes9x GX ULTIMATE
 *
 * menumusic.cpp
 *
 * Menu music: the OGG files of <APPFOLDER>/music (GCSettings.MenuMusic) and
 * the mini player of the menu. The OGG player reads the file playing from
 * the SD card or USB drive as it plays, and loops it (so files of any size
 * play, and changing the music does not stop the menu). The menu thread
 * (settings) and the GUI thread (player buttons) both use it, so everything
 * here takes a lock.
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
#include "filebrowser.h"
#include "utils/bezel.h"
#include "utils/oggplayer.h"

#ifdef HW_RVL

static const int musicDevices[] = { DEVICE_SD, DEVICE_USB };

static mutex_t musicLock = LWP_MUTEX_NULL;
static char (*names)[BEZEL_NAME_MAX] = NULL; // the music folder
static int count = 0;
static int current = -1;      // the file of names[] that is chosen, -1: none
static int state = MUSIC_STOPPED;
static bool oggActive = false; // the OGG player plays that file
static s32 resumeAt = 0;      // where to start again (ms) after a game ran
// The in-game menu plays its sound with the OGG player too: the music waits
// for it to start (1) and to end (2), or for a while if it is not heard.
static int waitEnterSound = 0;
static u64 waitSince = 0;
#define ENTER_SOUND_WAIT_MS 3000
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

static void Start(s32 at)
{
	StopPlayer();
	waitEnterSound = 0;
	char path[MAXPATHLEN];
	if(current < 0 || current >= count || !Find(names[current], path) ||
		PlayOggFile(path, at, OGG_INFINITE_TIME) < 0)
	{
		state = MUSIC_STOPPED;
		return;
	}
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
	if(current >= 0)
		Start(0);
	else
		state = MUSIC_STOPPED;
	changes++;
	Unlock();
}

void MenuMusicEnter()
{
	Lock();
	if(state == MUSIC_PLAYING && !oggActive)
	{
		if(SNESROMSize > 0)
		{
			waitEnterSound = 1; // MenuMusicTick() starts it after the sound
			waitSince = gettime();
		}
		else
			Start(resumeAt);
	}
	changes++;
	Unlock();
}

void MenuMusicLeave()
{
	Lock();
	waitEnterSound = 0;
	if(oggActive)
	{
		s32 at = GetTimeOgg();
		resumeAt = at > 0 ? at : 0;
		StopPlayer();
	}
	Unlock();
}

void MenuMusicTick()
{
	if(!waitEnterSound)
		return;
	Lock();
	bool running = (StatusOgg() == OGG_STATUS_RUNNING);
	if(waitEnterSound == 1 && running)
		waitEnterSound = 2; // the sound started
	else if((waitEnterSound == 2 && !running) ||
		(waitEnterSound == 1 && diff_msec(waitSince, gettime()) > ENTER_SOUND_WAIT_MS))
		Start(resumeAt);
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
		waitEnterSound = 0;
		state = MUSIC_PAUSED;
		changes++;
	}
	Unlock();
}

void MenuMusicStop()
{
	Lock();
	StopPlayer();
	waitEnterSound = 0;
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
void MenuMusicEnter() {}
void MenuMusicLeave() {}
void MenuMusicTick() {}
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
