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

#ifndef _DEFS_H_
#define _DEFS_H_
#ifdef __cplusplus
extern "C" {
#endif

/* clang required */
#if !defined(__clang__)
#error Clang is required
#endif

/* C23 required */
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 202311L
#error C23 or higher is required
#endif

/* wasm32 required */
#if defined(__wasm__) && !defined(__wasm32__)
#error only the wasm32 target is supported
#endif

/*
 * standard includes
 */

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

/*
 * engine progdefs
 */

#include "../progdefs.h"

/*
 * wasm macros
 */

#define WASM_EXPORT(n) __attribute((export_name(#n), used, visibility("default"))) n
#define WASM_IMPORT(n) __attribute((import_module("env"), import_name(#n))) n

/*
 * builtin funcitons provided by the compiler (hopefully)
 */

#define rint(f) __builtin_rint(f)
#define floor(f) __builtin_floor(f)
#define ceil(f) __builtin_ceil(f)
#define fabs(f) __builtin_fabs(f)
#define memcpy(dst, src, n) __builtin_memcpy(dst, src, n)
#define memset(dst, val, n) __builtin_memset(dst, val, n)
#define strlen(s) __builtin_strlen(s)
#define strcpy(dst, src) __builtin_strcpy(dst, src)
#define strncpy(dst, src, n) __builtin_strncpy(dst, src, n)

/*
 * vector math
 */

#define VectorCopy(dst, src) memcpy(dst, src, sizeof(vec3_t))
#define VectorDot(a, b) ((a)[0] * (b)[0] + (a)[1] * (b)[1] + (a)[2] * (b)[2])
#define VectorLength(b) VectorDot(v, v)

static inline void VectorCross(vec3_t dst, vec3_t a, vec3_t b)
{
	vec3_t c;
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
	VectorCopy(dst, c);
}

/*
 * builtin functions
 */

void WASM_IMPORT(makevectors)(vec3_t ang);
void WASM_IMPORT(setorigin)(entity_t e, vec3_t o);
void WASM_IMPORT(setmodel)(entity_t e, string_t m);
void WASM_IMPORT(setsize)(entity_t e, vec3_t min, vec3_t max);
float WASM_IMPORT(random)(void);
void WASM_IMPORT(sound)(entity_t e, float chan, string_t samp, float vol, float atten);
void WASM_IMPORT(normalize)(vec3_t v, vec3_t out);
void WASM_IMPORT(error)(string_t e);
void WASM_IMPORT(objerror)(string_t e);
float WASM_IMPORT(vlen)(vec3_t v);
float WASM_IMPORT(vectoyaw)(vec3_t v);
entity_t WASM_IMPORT(spawn)(void);
void WASM_IMPORT(remove)(entity_t e);
void WASM_IMPORT(traceline)(vec3_t v1, vec3_t v2, float nomonsters, entity_t forent);
entity_t WASM_IMPORT(checkclient)(void);
entity_t WASM_IMPORT(find)(entity_t start, string_t fld, string_t match);
string_t WASM_IMPORT(precache_sound)(string_t s);
string_t WASM_IMPORT(precache_model)(string_t s);
void WASM_IMPORT(stuffcmd)(entity_t client, string_t s);
entity_t WASM_IMPORT(findradius)(vec3_t org, float rad);
void WASM_IMPORT(bprint)(string_t s);
void WASM_IMPORT(sprint)(entity_t client, string_t s);
void WASM_IMPORT(dprint)(string_t s);
string_t WASM_IMPORT(ftos)(float f);
string_t WASM_IMPORT(vtos)(vec3_t v);
void WASM_IMPORT(coredump)(void);
void WASM_IMPORT(traceon)(void);
void WASM_IMPORT(traceoff)(void);
void WASM_IMPORT(eprint)(entity_t e);
float WASM_IMPORT(walkmove)(float yaw, float dist);
float WASM_IMPORT(droptofloor)(void);
void WASM_IMPORT(lightstyle)(float style, string_t value);
float WASM_IMPORT(checkbottom)(entity_t e);
float WASM_IMPORT(pointcontents)(vec3_t v);
void WASM_IMPORT(aim)(entity_t e, float speed, vec3_t out);
float WASM_IMPORT(cvar)(string_t s);
void WASM_IMPORT(localcmd)(string_t s);
entity_t WASM_IMPORT(nextent)(entity_t e);
void WASM_IMPORT(particle)(vec3_t o, vec3_t d, float color, float count);
void WASM_IMPORT(ChangeYaw)(void);
void WASM_IMPORT(vectoangles)(vec3_t v, vec3_t out);
void WASM_IMPORT(WriteByte)(float to, float f);
void WASM_IMPORT(WriteChar)(float to, float f);
void WASM_IMPORT(WriteShort)(float to, float f);
void WASM_IMPORT(WriteLong)(float to, float f);
void WASM_IMPORT(WriteCoord)(float to, float f);
void WASM_IMPORT(WriteAngle)(float to, float f);
void WASM_IMPORT(WriteString)(float to, string_t s);
void WASM_IMPORT(WriteEntity)(float to, entity_t s);
void WASM_IMPORT(movetogoal)(float step);
string_t WASM_IMPORT(precache_file)(string_t s);
void WASM_IMPORT(makestatic)(entity_t e);
void WASM_IMPORT(changelevel)(string_t s);
void WASM_IMPORT(cvar_set)(string_t var, string_t val);
void WASM_IMPORT(centerprint)(entity_t client, string_t s);
void WASM_IMPORT(ambientsound)(vec3_t pos, string_t samp, float vol, float atten);
string_t WASM_IMPORT(precache_model2)(string_t s);
string_t WASM_IMPORT(precache_sound2)(string_t s);
string_t WASM_IMPORT(precache_file2)(string_t s);
void WASM_IMPORT(setspawnparms)(entity_t e);

/*
 * constants
 */

enum : int32_t {
	FALSE = 0,
	TRUE = 1
};

/* edict.flags */
enum : int32_t {
	FL_FLY = 1,
	FL_SWIM = 2,
	FL_CLIENT = 8, /* set for all client edicts */
	FL_INWATER = 16, /* for enter / leave water splash */
	FL_MONSTER = 32,
	FL_GODMODE = 64, /* player cheat */
	FL_NOTARGET = 128, /* player cheat */
	FL_ITEM = 256, /* extra wide size for bonus items */
	FL_ONGROUND = 512, /* standing on something */
	FL_PARTIALGROUND = 1024, /* not all corners are valid */
	FL_WATERJUMP = 2048, /* player jumping out of water */
	FL_JUMPRELEASED = 4096 /* for jump debouncing */
};

/* edict.movetype values */
enum : int32_t {
	MOVETYPE_NONE = 0, /* never moves */
	MOVETYPE_WALK = 3, /* players only */
	MOVETYPE_STEP = 4, /* discrete, not real time unless fall */
	MOVETYPE_FLY = 5,
	MOVETYPE_TOSS = 6, /* gravity */
	MOVETYPE_PUSH = 7, /* no clip to world, push and crush */
	MOVETYPE_NOCLIP = 8,
	MOVETYPE_FLYMISSILE = 9, /* fly with extra size against monsters */
	MOVETYPE_BOUNCE = 10,
	MOVETYPE_BOUNCEMISSILE = 11 /* bounce with extra size */
};

/* edict.solid values */
enum : int32_t {
	SOLID_NOT = 0, /* no interaction with other objects */
	SOLID_TRIGGER = 1, /* touch on edge, but not blocking */
	SOLID_BBOX = 2, /* touch on edge, block */
	SOLID_SLIDEBOX = 3, /* touch on edge, but not an onground */
	SOLID_BSP = 4 /* bsp clip, touch on edge, block */
};

/* range values */
enum : int32_t {
	RANGE_MELEE = 0,
	RANGE_NEAR = 1,
	RANGE_MID = 2,
	RANGE_FAR = 3
};

/* deadflag values */
enum : int32_t {
	DEAD_NO = 0,
	DEAD_DYING = 1,
	DEAD_DEAD = 2,
	DEAD_RESPAWNABLE = 3
};

/* takedamage values */
enum : int32_t {
	DAMAGE_NO = 0,
	DAMAGE_YES = 1,
	DAMAGE_AIM = 2
};

/* items */
enum : int32_t {
	IT_AXE = 4096,
	IT_SHOTGUN = 1,
	IT_SUPER_SHOTGUN = 2,
	IT_NAILGUN = 4,
	IT_SUPER_NAILGUN = 8,
	IT_GRENADE_LAUNCHER = 16,
	IT_ROCKET_LAUNCHER = 32,
	IT_LIGHTNING = 64,
	IT_EXTRA_WEAPON = 128,

	IT_SHELLS = 256,
	IT_NAILS = 512,
	IT_ROCKETS = 1024,
	IT_CELLS = 2048,

	IT_ARMOR1 = 8192,
	IT_ARMOR2 = 16384,
	IT_ARMOR3 = 32768,
	IT_SUPERHEALTH = 65536,

	IT_KEY1 = 131072,
	IT_KEY2 = 262144,

	IT_INVISIBILITY = 524288,
	IT_INVULNERABILITY = 1048576,
	IT_SUIT = 2097152,
	IT_QUAD = 4194304
};

/* point content values */
enum : int32_t {
	CONTENT_EMPTY = -1,
	CONTENT_SOLID = -2,
	CONTENT_WATER = -3,
	CONTENT_SLIME = -4,
	CONTENT_LAVA = -5,
	CONTENT_SKY = -6
};

enum : int32_t {
	STATE_TOP = 0,
	STATE_BOTTOM = 1,
	STATE_UP = 2,
	STATE_DOWN = 3,
};

static const vec3_t VEC_ORIGIN = {0, 0, 0};
static const vec3_t VEC_HULL_MIN = {-16, -16, -24};
static const vec3_t VEC_HULL_MAX = {16, 16, 32};

static const vec3_t VEC_HULL2_MIN = {-32, -32, -24};
static const vec3_t VEC_HULL2_MAX = {32, 32, 64};

/* protocol bytes */
enum : uint8_t {
	SVC_TEMPENTITY = 23,
	SVC_KILLEDMONSTER = 27,
	SVC_FOUNDSECRET = 28,
	SVC_INTERMISSION = 30,
	SVC_FINALE = 31,
	SVC_CDTRACK = 32,
	SVC_SELLSCREEN = 33
};

enum : int32_t {
	TE_SPIKE = 0,
	TE_SUPERSPIKE = 1,
	TE_GUNSHOT = 2,
	TE_EXPLOSION = 3,
	TE_TAREXPLOSION = 4,
	TE_LIGHTNING1 = 5,
	TE_LIGHTNING2 = 6,
	TE_WIZSPIKE = 7,
	TE_KNIGHTSPIKE = 8,
	TE_LIGHTNING3 = 9,
	TE_LAVASPLASH = 10,
	TE_TELEPORT = 11
};

/*
 * sound channels
 * channel 0 never willingly overrides
 * other channels(1-7) allways override a playing sound on that channel
 */
enum : int32_t {
	CHAN_AUTO = 0,
	CHAN_WEAPON = 1,
	CHAN_VOICE = 2,
	CHAN_ITEM = 3,
	CHAN_BODY = 4
};

enum : int32_t {
	ATTN_NONE = 0,
	ATTN_NORM = 1,
	ATTN_IDLE = 2,
	ATTN_STATIC = 3
};

/* update types */
enum : int32_t {
	UPDATE_GENERAL = 0,
	UPDATE_STATIC = 1,
	UPDATE_BINARY = 2,
	UPDATE_TEMP = 3
};

/* entity effects */
enum : int32_t {
	EF_BRIGHTFIELD = 1,
	EF_MUZZLEFLASH = 2,
	EF_BRIGHTLIGHT = 4,
	EF_DIMLIGHT = 8
};

/* messages */
enum : int32_t {
	MSG_BROADCAST = 0, /* unreliable to all */
	MSG_ONE = 1, /* reliable to one(msg_entity) */
	MSG_ALL = 2, /* reliable to all */
	MSG_INIT = 3 /* write to the init string */
};

enum : int32_t {
	AS_STRAIGHT = 1,
	AS_SLIDING = 2,
	AS_MELEE = 3,
	AS_MISSILE = 4
};

/*
 * progs exports
 */

/* main.c */
extern globalvars_t globals;

/* client.c */
void PlayerPreThink(void);
void PlayerPostThink(void);
void ClientKill(void);
void ClientConnect(void);
void PutClientInServer(void);
void ClientDisconnect(void);

/* world.c */
void StartFrame(void);

#ifdef __cplusplus
}
#endif
#endif /* _DEFS_H_ */
