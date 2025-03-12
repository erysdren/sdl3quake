
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

/* import/export helper macros */
#define PR_EXPORT(n) __attribute__((export_name(#n), used, visibility("default"))) n
#define PR_IMPORT(n) __attribute__((import_module("env"), import_name(#n))) n

/*
 * entity type
 */

typedef struct entity {
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
	void (*touch)(struct entity *self, struct entity *other);
	void (*use)(struct entity *self, struct entity *activator);
	void (*think)(struct entity *self);
	void (*blocked)(struct entity *self);
	float nextthink;
	struct entity *groundentity;
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
	struct entity *chain;
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
	struct entity *enemy;
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
	struct entity *aiment;
	struct entity *goalentity;
	float spawnflags;
	const char *target;
	const char *targetname;
	float dmg_take;
	float dmg_save;
	struct entity *dmg_inflictor;
	struct entity *owner;
	vec3_t movedir;
	const char *message;
	float sounds;
	const char *noise;
	const char *noise1;
	const char *noise2;
	const char *noise3;
} entity_t;

/*
 * game code imports
 */

entity_t *PR_IMPORT(spawn)(void); /**< create a new entity */
void PR_IMPORT(remove)(entity_t *e); /**< remove the specified entity */
void PR_IMPORT(print)(const char *s); /**< print to the server console */

/*
 * game code exports
 */

#ifdef SERVER
void PR_EXPORT(StartFrame)(entity_t *self); /**< called before physics are run every frame */
void PR_EXPORT(EndFrame)(entity_t *self); /**< called after physics are run every frame */
void PR_EXPORT(ClientStartFrame)(entity_t *self); /**< called for each client before physics are run every frame */
void PR_EXPORT(ClientEndFrame)(entity_t *self); /**< called for each client after physics are run every frame */
void PR_EXPORT(ClientConnect)(entity_t *self); /**< called for each client when they have fully connected */
void PR_EXPORT(ClientDisconnect)(entity_t *self); /**< called for each client when they disconnect */
void PR_EXPORT(ClientSetNewParms)(entity_t *self); /**< called for each client when starting a new level unit */
void PR_EXPORT(ClientSetChangeParms)(entity_t *self); /**< called for each client when they're about to go through a level transition */
#endif
#ifdef CLIENT
void PR_EXPORT(DrawHud)(int w, int h); /**< called each frame for drawing the hud */
#endif

#ifdef __cplusplus
}
#endif
#endif /* _DEFS_H_ */
