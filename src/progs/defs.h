
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

/* vector types required */
#if !__has_attribute(ext_vector_type)
#error the ext_vector_type attribute is required
#endif

/* standard includes */
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

/* vector type */
typedef float vec3_t __attribute__((ext_vector_type(3)));
#define vec3(x, y, z) (vec3_t){x, y, z}

/* entity type */
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
	const char *classname;
	const char *model;
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
	entity_t *groundentity;
	float health;
	float frags;
	float weapon;
	const char *weaponmodel;
	float weaponframe;
	float currentammo;
	float ammo_shells;
	float ammo_nails;
	float ammo_rockets;
	float ammo_cells;
	float items;
	float takedamage;
	entity_t *chain;
	float deadflag;
	vec3_t view_ofs;
	float button0;
	float button1;
	float button2;
	float impulse;
	float fixangle;
	vec3_t v_angle;
	float idealpitch;
	const char *netname;
	entity_t *enemy;
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
	entity_t *aiment;
	entity_t *goalentity;
	float spawnflags;
	const char *target;
	const char *targetname;
	float dmg_take;
	float dmg_save;
	entity_t *dmg_inflictor;
	entity_t *owner;
	vec3_t movedir;
	const char *message;
	float sounds;
	const char *noise;
	const char *noise1;
	const char *noise2;
	const char *noise3;
} entvars_t;

/* these are for the wasm gamecode only */
#if defined(__wasm__)
#define PR_EXPORT(n) __attribute__((export_name(#n), used, visibility("default"))) n
#define PR_IMPORT(n) __attribute__((import_module("env"), import_name(#n))) n
void PR_EXPORT(StartFrame)(void);
void PR_EXPORT(PlayerPreThink)(void);
void PR_EXPORT(PlayerPostThink)(void);
void PR_EXPORT(ClientKill)(void);
void PR_EXPORT(ClientConnect)(void);
void PR_EXPORT(PutClientInServer)(void);
void PR_EXPORT(ClientDisconnect)(void);
void PR_EXPORT(SetNewParms)(void);
void PR_EXPORT(SetChangeParms)(void);
#else
#define PR_EXPORT(n) n
#define PR_IMPORT(n) n
#endif

#ifdef __cplusplus
}
#endif
#endif /* _DEFS_H_ */
