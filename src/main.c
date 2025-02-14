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

#include "quakedef.h"
#include "sdl3quake.h"

#include <assert.h>
#include <SDL3/SDL.h>
#include <stdint.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;
static SDL_Surface *surface8 = NULL;
static SDL_Surface *surface24 = NULL;
static SDL_Palette *palette = NULL;

#define KEYBUFFERSIZE	32
static int keybuffer[KEYBUFFERSIZE];  // circular key buffer
static int keybuffer_len;  // number of keys in the buffer
static int keybuffer_start;  // index of next item to be read

static int mouse_x, mouse_y;
static float joy_axes[QUAKEGENERIC_JOY_MAX_AXES];
static SDL_Joystick *joystick;

void QG_Tick(double duration)
{
	Host_Frame(duration);
}

void QG_Create(int argc, char *argv[])
{
	static quakeparms_t    parms;

	parms.memsize = 8*1024*1024;
	parms.membase = malloc (parms.memsize);
	parms.basedir = ".";

	COM_InitArgv (argc, argv);

	parms.argc = com_argc;
	parms.argv = com_argv;

	printf ("Host_Init\n");
	Host_Init (&parms);
}

void QG_Init(void)
{
	// init sdl
	SDL_Init(SDL_INIT_VIDEO);

	// create window
	window = SDL_CreateWindow(GAMETITLE, BASEWIDTH, BASEHEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
	SDL_SetWindowMinimumSize(window, BASEWIDTH, BASEHEIGHT);

	// create renderer
	renderer = SDL_CreateRenderer(window, NULL);
	SDL_SetRenderLogicalPresentation(renderer, BASEWIDTH, BASEHEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	// get window pixel format
	SDL_PixelFormat window_format = SDL_GetWindowPixelFormat(window);

	// create texture
	texture = SDL_CreateTexture(renderer, window_format, SDL_TEXTUREACCESS_STREAMING, BASEWIDTH, BASEHEIGHT);
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

	// create draw surface
	surface8 = SDL_CreateSurfaceFrom(BASEWIDTH, BASEHEIGHT, SDL_PIXELFORMAT_INDEX8, NULL, BASEWIDTH);
	palette = SDL_CreateSurfacePalette(surface8);

	// create screen surface
	surface24 = SDL_CreateSurfaceFrom(BASEWIDTH, BASEHEIGHT, window_format, NULL, BASEWIDTH * SDL_BYTESPERPIXEL(window_format));

	SDL_SetWindowRelativeMouseMode(window, true);

	keybuffer_len = 0;
	keybuffer_start = 0;
	mouse_x = mouse_y = 0;
	memset(joy_axes, 0, sizeof(joy_axes));

	int num_joysticks = 0;
	SDL_JoystickID *joysticks = SDL_GetJoysticks(&num_joysticks);

    if (joysticks)
		joystick = SDL_OpenJoystick(0);
	else
		joystick = NULL;

	SDL_free(joysticks);
}

static int ConvertToQuakeButton(unsigned char button)
{
	int qbutton;

	switch (button)
	{
		case 1:
			qbutton = K_MOUSE1;
			break;
		case 2:
			qbutton = K_MOUSE3;
			break;
		case 3:
			qbutton = K_MOUSE2;
			break;
		default:
			qbutton = -1;
			break;
	}
	return qbutton;
}

static int ConvertToQuakeKey(unsigned int key)
{
	int qkey;

	switch (key)
	{
		case SDLK_TAB:
			qkey = K_TAB;
			break;
		case SDLK_RETURN:
			qkey = K_ENTER;
			break;
		case SDLK_ESCAPE:
			qkey = K_ESCAPE;
			break;
		case SDLK_SPACE:
			qkey = K_SPACE;
			break;
		case SDLK_BACKSPACE:
			qkey = K_BACKSPACE;
			break;
		case SDLK_UP:
			qkey = K_UPARROW;
			break;
		case SDLK_DOWN:
			qkey = K_DOWNARROW;
			break;
		case SDLK_LEFT:
			qkey = K_LEFTARROW;
			break;
		case SDLK_RIGHT:
			qkey = K_RIGHTARROW;
			break;
		case SDLK_LALT:
		case SDLK_RALT:
			qkey = K_ALT;
			break;
		case SDLK_LCTRL:
		case SDLK_RCTRL:
			qkey = K_CTRL;
			break;
		case SDLK_LSHIFT:
		case SDLK_RSHIFT:
			qkey = K_SHIFT;
			break;
		case SDLK_F1:
			qkey = K_F1;
			break;
		case SDLK_F2:
			qkey = K_F2;
			break;
		case SDLK_F3:
			qkey = K_F3;
			break;
		case SDLK_F4:
			qkey = K_F4;
			break;
		case SDLK_F5:
			qkey = K_F5;
			break;
		case SDLK_F6:
			qkey = K_F6;
			break;
		case SDLK_F7:
			qkey = K_F7;
			break;
		case SDLK_F8:
			qkey = K_F8;
			break;
		case SDLK_F9:
			qkey = K_F9;
			break;
		case SDLK_F10:
			qkey = K_F10;
			break;
		case SDLK_F11:
			qkey = K_F11;
			break;
		case SDLK_F12:
			qkey = K_F12;
			break;
		case SDLK_INSERT:
			qkey = K_INS;
			break;
		case SDLK_DELETE:
			qkey = K_DEL;
			break;
		case SDLK_PAGEDOWN:
			qkey = K_PGDN;
			break;
		case SDLK_PAGEUP:
			qkey = K_PGUP;
			break;
		case SDLK_HOME:
			qkey = K_HOME;
			break;
		case SDLK_END:
			qkey = K_END;
			break;
		case SDLK_PAUSE:
			qkey = K_PAUSE;
			break;
		default:
			qkey = SDL_tolower(key);
			break;

		/*
		 * Not yet converted:
		 *   K_JOY*
		 *   K_AUX*
		 */
	}

	return qkey;
}

static int KeyPop(int *down, int *key)
{
	if (keybuffer_len == 0)
		return 0; // underflow

	*key = keybuffer[keybuffer_start];
	*down = *key < 0;
	if (*key < 0)
		*key = -*key;
	keybuffer_start = (keybuffer_start + 1) % KEYBUFFERSIZE;
	keybuffer_len--;

	return 1;
}

static int KeyPush(int down, int key)
{
	if (keybuffer_len == KEYBUFFERSIZE)
		return 0; // overflow
	assert(key > 0);
	if (down) {
		key = -key;
	}
	keybuffer[(keybuffer_start + keybuffer_len) % KEYBUFFERSIZE] = key;
	keybuffer_len++;

	return 1;
}

int QG_GetKey(int *down, int *key)
{
	return KeyPop(down, key);
}

void QG_GetJoyAxes(float *axes)
{
	memcpy(axes, joy_axes, sizeof(joy_axes));
}

void QG_GetMouseMove(int *x, int *y)
{
	*x = mouse_x;
	*y = mouse_y;

	mouse_x = mouse_y = 0;
}

void QG_Quit(void)
{
	if (window) SDL_DestroyWindow(window);
	if (renderer) SDL_DestroyRenderer(renderer);
	if (texture) SDL_DestroyTexture(texture);
	if (surface8) SDL_DestroySurface(surface8);
	if (surface24) SDL_DestroySurface(surface24);
	if (joystick != NULL) SDL_CloseJoystick(joystick);
	SDL_Quit();
}

void QG_DrawFrame(void *pixels)
{
	surface8->pixels = pixels;
	surface8->pitch = BASEWIDTH;

	if (SDL_LockTexture(texture, NULL, &surface24->pixels, &surface24->pitch))
	{
		SDL_BlitSurface(surface8, NULL, surface24, NULL);
		SDL_UnlockTexture(texture);
	}

	SDL_RenderClear(renderer);
	SDL_RenderTexture(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void QG_SetPalette(unsigned char pal[768])
{
	for (int i = 0; i < 256; i++)
	{
		palette->colors[i].r = pal[i * 3 + 0];
		palette->colors[i].g = pal[i * 3 + 1];
		palette->colors[i].b = pal[i * 3 + 2];
		palette->colors[i].a = 255;
	}
}

int main(int argc, char *argv[])
{
	double oldtime, newtime;
	int running = 1;
	int button;

	QG_Create(argc, argv);

	oldtime = (double)SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency() - 0.1;
	while (running)
	{
		// poll events
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_EVENT_QUIT:
					running = 0;
					break;
				case SDL_EVENT_KEY_DOWN:
				case SDL_EVENT_KEY_UP:
					(void) KeyPush((event.type == SDL_EVENT_KEY_DOWN), ConvertToQuakeKey(event.key.key));
					break;
				case SDL_EVENT_MOUSE_MOTION:
					mouse_x += event.motion.xrel;
					mouse_y += event.motion.yrel;
					break;
				case SDL_EVENT_MOUSE_BUTTON_DOWN:
				case SDL_EVENT_MOUSE_BUTTON_UP:
					button = ConvertToQuakeButton(event.button.button);
					if (button != -1) {
						(void) KeyPush((event.type == SDL_EVENT_MOUSE_BUTTON_DOWN), button);
					}
					break;
				case SDL_EVENT_MOUSE_WHEEL:
					if (event.wheel.y > 0)
					{
						(void) KeyPush(1, K_MWHEELUP);
						(void) KeyPush(0, K_MWHEELUP);
					}
					else if (event.wheel.y < 0)
					{
						(void) KeyPush(1, K_MWHEELDOWN);
						(void) KeyPush(0, K_MWHEELDOWN);
					}
					break;
				case SDL_EVENT_JOYSTICK_AXIS_MOTION:
					if (event.jaxis.axis < QUAKEGENERIC_JOY_MAX_AXES) {
						joy_axes[event.jaxis.axis] = event.jaxis.value / 32767.0f;
					}
					break;

				case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
				case SDL_EVENT_JOYSTICK_BUTTON_UP:
					button = event.jbutton.button + ((event.jbutton.button < 4) ? K_JOY1 : K_AUX1);
					(void) KeyPush((event.type == SDL_EVENT_JOYSTICK_BUTTON_DOWN), button);
					break;
			}
		}

		// HACKHACK: disable mouselook while in menu
		if (key_dest == key_menu)
			SDL_SetWindowRelativeMouseMode(window, false);
		else
			SDL_SetWindowRelativeMouseMode(window, true);

		// Run the frame at the correct duration.
		newtime = (double)SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency();
		QG_Tick(newtime - oldtime);
		oldtime = newtime;
	}

	return 0;
}
