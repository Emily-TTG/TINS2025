#pragma once

#include <pdn/local.h>

#include <pdn/context.h>
#include <pdn/detail.h>
#include <pdn/log.h>
#include <pdn/components.h>
#include <pdn/script.h>
#include <pdn/tilemap.h>

#include <pdn/result.h>
#include <pdn/log.h>
#include <pdn/context.h>
#include <pdn/settings.h>
#include <pdn/scene.h>
#include <pdn/detail.h>
#include <pdn/script.h>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <stdlib.h>
#include <time.h>
#include <math.h>

struct gm_camera {
	float x, y;
	float zoom;

	float jitter;
	float color_pulse;

	float light_floor;
};

struct gm_light {
	float x, y;
	ALLEGRO_COLOR color;

	float linear, quadratic;
	float clamp;
};

#define GM_WEAPON_BASE (24)
enum gm_weapon {
	GM_WEAPON_EGG,
	GM_WHISK,
	GM_WEAPON_SALT,
	GM_WEAPON_PEPPER,
	GM_WEAPON_BURNER,
	GM_WEAPON_SAP,
	GM_WEAPON_COUNT
};

enum gm_enemy_type {
	GM_DEMON_0,
	GM_DEMON_1,
	GM_DEMON_2,
	GM_DEMON_3,
	GM_ENEMY_COUNT
};

#define GM_PROJECTILE_BASE (44)
enum gm_projectile_type {
	GM_NONE,
	GM_BURGER,
	GM_ANGEL,
	GM_BREADCRUMB,
	GM_EGG,
	GM_EGG2,
	GM_SALT,
	GM_PEPPER,
	GM_FLAME,
	GM_SAP,
	GM_PROJECTILE_COUNT
};

extern struct gm_weapon_info {
	const char* name;
	float radius;
	float damage;
	float knockback;
	float cost;
	bool melee;
	enum gm_projectile_type projectile;
	bool owned;
} gm_global_weapon_info[GM_WEAPON_COUNT];

extern struct gm_enemy_info {
	const char* name;
	float health;
	float dampening;
	float width_mul;
	int tid;
	enum gm_projectile_type projectile;
	float follow_force, force_cap, follow_distance, min_distance;
	const char* sample_path;
	ALLEGRO_SAMPLE* sample;
	float itime;
	int cash;
} gm_global_enemy_info[GM_ENEMY_COUNT];

extern struct gm_projectile_info {
	const char* name;
	float reload;
	int burst;
	float burst_interval;
	float damage;
	float force;
	int tid;
	float animate_time;
	float lifetime;
	const char* sample_path;
	ALLEGRO_SAMPLE* sample;
	float radius;
	float growth;
	const char* shhot_path;
	ALLEGRO_SAMPLE* shhot;
} gm_global_projectile_info[GM_PROJECTILE_COUNT];

typedef struct gm_enemy {
	enum gm_enemy_type type;
	float health;
	int burst;
	float since_fired;
	float time_since_hit;
} gm_component_enemy_t;

typedef struct gm_projectile {
	enum gm_projectile_type type;
	bool player;
	float since_animate;
	float life;
	int alt_tid;
} gm_component_projectile_t;

typedef struct gm_physics {
	float vx, vy;
	float dampening;
} gm_component_physics_t;

typedef struct gm_component_sprite_aux_t {
	bool flip;
	float rot;
	float ex_scale;
	ALLEGRO_COLOR invtint;
} gm_component_sprite_aux_t;

enum gm_pickup_type {
	GM_WEAPON,
	GM_KEY,
	GM_UNION
};

typedef struct gm_pickup {
	enum gm_pickup_type type;
	int price;
	enum gm_weapon weapon;
} gm_component_pickup_t;

extern ECS_COMPONENT_DECLARE(gm_component_enemy_t);
extern ECS_COMPONENT_DECLARE(gm_component_physics_t);
extern ECS_COMPONENT_DECLARE(gm_component_projectile_t);
extern ECS_COMPONENT_DECLARE(gm_component_sprite_aux_t);
extern ECS_COMPONENT_DECLARE(gm_component_pickup_t);

struct gm_oven {
	bool spawned;
	float timer;
	float x, y;
	float bx, by;
	float health;
	float max_health;
	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_SAMPLE* death;
	ALLEGRO_SAMPLE* yow;
	float itime, time_since_hit;
};

extern struct gm_state {
	ecs_entity_t player;
	float aim;
	float w_x, w_y;
	float wdx, wdy;
	float oldx, oldy;
	enum gm_weapon weapon;
	float time_since_damage, itime;
	float time_since_fired;
	ALLEGRO_SAMPLE* hit;

	ALLEGRO_SAMPLE_ID current;
	ALLEGRO_SAMPLE* main_music;
	ALLEGRO_SAMPLE* end_music;
	ALLEGRO_SAMPLE* death;

	ALLEGRO_SAMPLE* key_pick;
	ALLEGRO_SAMPLE* weapon_pick;
	ALLEGRO_SAMPLE* union_pick;

	ALLEGRO_BITMAP* full;
	ALLEGRO_BITMAP* empty;
	ALLEGRO_BITMAP* reload_full;
	ALLEGRO_BITMAP* reload_empty;
	ALLEGRO_BITMAP* marker;
	ALLEGRO_BITMAP* pwmarker;
	float fullness;
	float max_fullness;

	ALLEGRO_KEYBOARD_STATE keyboard;

	int money, keys;

	ecs_world_t* world;
	struct pdn_tileset object_tileset;

	struct pdn_tilemap map;

	struct gm_camera camera;
	struct gm_light light;

	float death_timeout;
	time_t start;
	int weapons;

	int enemies, nenemies;
	int tkeys, nkeys;

	float credits_timeout;
	bool in_credits;

	float jitter_falloff, pulse_falloff;

	float width, height;

	struct gm_oven oven;
} gm_global_state;

enum pdn_result pdn_tilemap_script_table_handler_patched(struct pdn_script*, const char*, void*);

float gm_light_attenuate(struct gm_light* light, struct gm_camera* camera, float x, float y);
float gm_random(void);
float gm_sign_random(void);

ALLEGRO_COLOR gm_color_multiply(ALLEGRO_COLOR color, float value);
ALLEGRO_COLOR gm_color_add_color(ALLEGRO_COLOR color, ALLEGRO_COLOR other);
ALLEGRO_COLOR gm_color_sub_color(ALLEGRO_COLOR color, ALLEGRO_COLOR other);
ALLEGRO_COLOR gm_color_random();
ALLEGRO_COLOR gm_color_multiply_color(ALLEGRO_COLOR color, ALLEGRO_COLOR other);

void gm_render_tilemap(ecs_iter_t* it);
void gm_render_sprite(ecs_iter_t* it);
void gm_update_enemy(ecs_iter_t* it);
void gm_update_physics(ecs_iter_t* it);
void gm_update_projectile(ecs_iter_t* it);
void gm_update_pickup(ecs_iter_t* it);

extern ECS_SYSTEM_DECLARE(gm_render_tilemap);
extern ECS_SYSTEM_DECLARE(gm_render_sprite);
extern ECS_SYSTEM_DECLARE(gm_update_enemy);
extern ECS_SYSTEM_DECLARE(gm_update_physics);
extern ECS_SYSTEM_DECLARE(gm_update_projectile);
extern ECS_SYSTEM_DECLARE(gm_update_pickup);

#define GM_MAX(a, b) ((a) > (b) ? (a) : (b))
#define GM_MIN(a, b) ((a) < (b) ? (a) : (b))
