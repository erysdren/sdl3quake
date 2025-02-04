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

// r_vars.c: global refresh variables

#include	"quakedef.h"

// all global and static refresh variables are collected in a contiguous block
// to avoid cache conflicts.

//-------------------------------------------------------
// global refresh variables
//-------------------------------------------------------

// FIXME: make into one big structure, like cl or sv
// FIXME: do separately for refresh engine and driver

float	d_sdivzstepu, d_tdivzstepu, d_zistepu;
float	d_sdivzstepv, d_tdivzstepv, d_zistepv;
float	d_sdivzorigin, d_tdivzorigin, d_ziorigin;

fixed16_t	sadjust, tadjust, bbextents, bbextentt;

uint8_t			*cacheblock;
int				cachewidth;
uint8_t			*d_viewbuffer;
int16_t			*d_pzbuffer;
unsigned int	d_zrowbytes;
unsigned int	d_zwidth;
