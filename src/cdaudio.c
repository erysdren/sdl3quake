/*
Copyright (C) 1996-1997 Id Software, Inc.
Copyright (C) 2025 erysdren (it/its)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see https://www.gnu.org/licenses/
*/

#include <SDL3_mixer/SDL_mixer.h>

#include "quakedef.h"

static qboolean initialized = false;
static Mix_Music *current_music = NULL;

void CDAudio_Play(byte track, qboolean looping)
{
	char path[MAX_OSPATH];
	void *data;
	SDL_IOStream *io;

	if (!initialized)
		return;

	CDAudio_Stop();

	snprintf(path, sizeof(path), "music/track%02d.ogg", track);

	data = (void *)COM_LoadFile(path, 0);

	if (data == NULL)
		return;

	io = SDL_IOFromConstMem(data, com_filesize);
	current_music = Mix_LoadMUS_IO(io, true);

	if (current_music == NULL)
		return;

	Mix_PlayMusic(current_music, looping ? -1 : 1);

	Z_Free(data);
}


void CDAudio_Stop(void)
{
	if (!initialized)
		return;

	Mix_HaltMusic();

	if (current_music)
		Mix_FreeMusic(current_music);

	current_music = NULL;
}


void CDAudio_Pause(void)
{
	if (!initialized)
		return;

	Mix_PauseMusic();
}


void CDAudio_Resume(void)
{
	if (!initialized)
		return;

	Mix_ResumeMusic();
}


void CDAudio_Update(void)
{
	extern cvar_t bgmvolume;
	int vol = MIX_MAX_VOLUME;

	vol = (int)(bgmvolume.value * MIX_MAX_VOLUME);
	if(vol < 0) { vol = 0; }
	if(vol > MIX_MAX_VOLUME) { vol = MIX_MAX_VOLUME; }

	Mix_VolumeMusic(vol);
}


int CDAudio_Init(void)
{
	SDL_AudioSpec spec = {
		.format = MIX_DEFAULT_FORMAT,
		.channels = MIX_DEFAULT_CHANNELS,
		.freq = MIX_DEFAULT_FREQUENCY
	};

	if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG)
	{
		Con_Printf("Mix_Init: %s\n", SDL_GetError());
		return -1;
	}

	if (!Mix_OpenAudio(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec))
	{
		Con_Printf("Mix_OpenAudio: %s\n", SDL_GetError());
		Mix_Quit();
		return -1;
	}

	initialized = true;

	return 0;
}


void CDAudio_Shutdown(void)
{
	if (!initialized)
		return;

	CDAudio_Stop();
	Mix_CloseAudio();
	Mix_Quit();

	initialized = false;
}
