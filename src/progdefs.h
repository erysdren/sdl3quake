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

#ifndef _PROGDEFS_H_
#define _PROGDEFS_H_

#if defined(__wasm__)
typedef const char *string_t;
typedef float vec3_t[3];
typedef void (*func_t)(void);
typedef struct entvars *entity_t;
#define ENTITY_T entity_t
#else
#define ENTITY_T uint32_t
#endif

typedef struct globalvars {
	uint8_t pad[4 * 28];
	ENTITY_T self;
	ENTITY_T other;
	ENTITY_T world;
	float time;
	float frametime;
	float force_retouch;
	string_t mapname;
	float deathmatch;
	float coop;
	float teamplay;
	float serverflags;
	float total_secrets;
	float total_monsters;
	float found_secrets;
	float killed_monsters;
	float parm1;
	float parm2;
	float parm3;
	float parm4;
	float parm5;
	float parm6;
	float parm7;
	float parm8;
	float parm9;
	float parm10;
	float parm11;
	float parm12;
	float parm13;
	float parm14;
	float parm15;
	float parm16;
	vec3_t v_forward;
	vec3_t v_up;
	vec3_t v_right;
	float trace_allsolid;
	float trace_startsolid;
	float trace_fraction;
	vec3_t trace_endpos;
	vec3_t trace_plane_normal;
	float trace_plane_dist;
	ENTITY_T trace_ent;
	float trace_inopen;
	float trace_inwater;
	ENTITY_T msg_entity;
	func_t main;
	func_t StartFrame;
	func_t PlayerPreThink;
	func_t PlayerPostThink;
	func_t ClientKill;
	func_t ClientConnect;
	func_t PutClientInServer;
	func_t ClientDisconnect;
	func_t SetNewParms;
	func_t SetChangeParms;
} globalvars_t;

typedef struct entvars {
	float modelindex;
	vec3_t absmin;
	vec3_t absmax;
	float ltime;
	float movetype;
	float solid;
	vec3_t origin;
	vec3_t oldorigin;
	vec3_t velocity;
	vec3_t angles;
	vec3_t avelocity;
	vec3_t punchangle;
	string_t classname;
	string_t model;
	float frame;
	float skin;
	float effects;
	vec3_t mins;
	vec3_t maxs;
	vec3_t size;
	func_t touch;
	func_t use;
	func_t think;
	func_t blocked;
	float nextthink;
	ENTITY_T groundentity;
	float health;
	float frags;
	float weapon;
	string_t weaponmodel;
	float weaponframe;
	float currentammo;
	float ammo_shells;
	float ammo_nails;
	float ammo_rockets;
	float ammo_cells;
	float items;
	float takedamage;
	ENTITY_T chain;
	float deadflag;
	vec3_t view_ofs;
	float button0;
	float button1;
	float button2;
	float impulse;
	float fixangle;
	vec3_t v_angle;
	float idealpitch;
	string_t netname;
	ENTITY_T enemy;
	float flags;
	float colormap;
	float team;
	float max_health;
	float teleport_time;
	float armortype;
	float armorvalue;
	float waterlevel;
	float watertype;
	float ideal_yaw;
	float yaw_speed;
	ENTITY_T aiment;
	ENTITY_T goalentity;
	float spawnflags;
	string_t target;
	string_t targetname;
	float dmg_take;
	float dmg_save;
	ENTITY_T dmg_inflictor;
	ENTITY_T owner;
	vec3_t movedir;
	string_t message;
	float sounds;
	string_t noise;
	string_t noise1;
	string_t noise2;
	string_t noise3;
} entvars_t;

#undef ENTITY_T

#endif /* _PROGDEFS_H_ */
