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

//
// modelgen.h: header file for model generation program
//

// *********************************************************
// * This file must be identical in the modelgen directory *
// * and in the Quake directory, because it's used to      *
// * pass data from one to the other via model files.      *
// *********************************************************

#ifdef INCLUDELIBS

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "cmdlib.h"
#include "scriplib.h"
#include "trilib.h"
#include "lbmlib.h"
#include "mathlib.h"

#endif

#define ALIAS_VERSION	6

#define ALIAS_ONSEAM				0x0020

// must match definition in spritegn.h
#ifndef SYNCTYPE_T
#define SYNCTYPE_T
typedef enum : int32_t { ST_SYNC=0, ST_RAND } synctype_t;
#endif

typedef enum : int32_t { ALIAS_SINGLE=0, ALIAS_GROUP } aliasframetype_t;

typedef enum : int32_t { ALIAS_SKIN_SINGLE=0, ALIAS_SKIN_GROUP } aliasskintype_t;

typedef struct {
	int32_t		ident;
	int32_t		version;
	vec3_t		scale;
	vec3_t		scale_origin;
	float		boundingradius;
	vec3_t		eyeposition;
	int32_t		numskins;
	int32_t		skinwidth;
	int32_t		skinheight;
	int32_t		numverts;
	int32_t		numtris;
	int32_t		numframes;
	synctype_t	synctype;
	int32_t		flags;
	float		size;
} mdl_t;

// TODO: could be shorts

typedef struct {
	int32_t	onseam;
	int32_t	s;
	int32_t	t;
} stvert_t;

typedef struct dtriangle_s {
	int32_t				facesfront;
	int32_t				vertindex[3];
} dtriangle_t;

#define DT_FACES_FRONT				0x0010

// This mirrors trivert_t in trilib.h, is present so Quake knows how to
// load this data

typedef struct {
	uint8_t	v[3];
	uint8_t	lightnormalindex;
} trivertx_t;

typedef struct {
	trivertx_t	bboxmin;	// lightnormal isn't used
	trivertx_t	bboxmax;	// lightnormal isn't used
	char		name[16];	// frame name from grabbing
} daliasframe_t;

typedef struct {
	int32_t		numframes;
	trivertx_t	bboxmin;	// lightnormal isn't used
	trivertx_t	bboxmax;	// lightnormal isn't used
} daliasgroup_t;

typedef struct {
	int32_t		numskins;
} daliasskingroup_t;

typedef struct {
	float	interval;
} daliasinterval_t;

typedef struct {
	float	interval;
} daliasskininterval_t;

typedef struct {
	aliasframetype_t	type;
} daliasframetype_t;

typedef struct {
	aliasskintype_t	type;
} daliasskintype_t;

#define IDPOLYHEADER	(('O'<<24)+('P'<<16)+('D'<<8)+'I')
														// little-endian "IDPO"

