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

#include "defs.h"

globalvars_t globals;

void StartFrame(void)
{

}

void PlayerPreThink(void)
{

}

void PlayerPostThink(void)
{

}

void ClientKill(void)
{

}

void ClientConnect(void)
{

}

void PutClientInServer(void)
{

}

void ClientDisconnect(void)
{

}

globalvars_t *WASM_EXPORT(GetGameAPI)(void)
{
	__builtin_memset(&globals, 0, sizeof(globalvars_t));

	globals.StartFrame = StartFrame;
	globals.PlayerPreThink = PlayerPreThink;
	globals.PlayerPostThink = PlayerPostThink;
	globals.ClientKill = ClientKill;
	globals.ClientConnect = ClientConnect;
	globals.PutClientInServer = PutClientInServer;
	globals.ClientDisconnect = ClientDisconnect;

	return &globals;
}
