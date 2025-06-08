ECS_COMPONENT_DECLARE(gm_component_enemy_t);
ECS_COMPONENT_DECLARE(gm_component_physics_t);
ECS_COMPONENT_DECLARE(gm_component_projectile_t);
ECS_COMPONENT_DECLARE(gm_component_sprite_aux_t);
ECS_COMPONENT_DECLARE(gm_component_pickup_t);

ECS_SYSTEM_DECLARE(gm_render_tilemap);
ECS_SYSTEM_DECLARE(gm_render_sprite);
ECS_SYSTEM_DECLARE(gm_update_enemy);
ECS_SYSTEM_DECLARE(gm_update_physics);
ECS_SYSTEM_DECLARE(gm_update_projectile);
ECS_SYSTEM_DECLARE(gm_update_pickup);

static enum pdn_result pdn_main(int argc, char** argv) {
	enum pdn_result result;

	struct pdn_context_detail detail = {};

	struct pdn_settings settings = {};
	struct pdn_display display = {};
	struct pdn_ui ui = {};
	struct pdn_scene scene = {};

	struct pdn_context context = {
			.detail = &detail,

			.settings = &settings,
			.display = &display,
			.ui = &ui,
			.scene = &scene
	};

	struct pdn_context_options options = {
			.font = "res/font/unitblock/unitblock.ttf",
			.style = "res/style/game_nk_style.bin"
	};

	if(!al_filename_exists("res/font/unitblock/unitblock.ttf")) {
		if(al_filename_exists("../res/font/unitblock/unitblock.ttf")) {
			al_change_directory("..");
		}
		else {
			if(al_filename_exists("../../res/font/unitblock/unitblock.ttf")) {
				al_change_directory("../..");
			}
			else return PDN_LOG_RESULT_PATH(al_filename_exists, "res/", PDN_RESULT_ERROR);
		}
	}

	result = pdn_context_new(&context, &options, argc, argv);
	if(result) {
		return PDN_LOG_RESULT("pdn_context_new", result);
	}

	result = pdn_context_loop(&context);
	if(result) {
		return PDN_LOG_RESULT("pdn_context_loop", result);
	}

	pdn_context_delete(&context);

	return PDN_RESULT_OK;
}

int main(int argc, char** argv) {
	enum pdn_result result = pdn_main(argc, argv);

	if(result) {
		(void) PDN_LOG_RESULT("pdn_main", result);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

struct gm_state gm_global_state;

enum pdn_result pdn_local_start(struct pdn_context* context) {
	srand(time(0));

	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(32);

	gm_global_state = (struct gm_state) {
			.camera = {
					.x = 0.0f,
					.y = 0.0f,
					.zoom = 3.0f,
					.jitter = 0.0f,
					.light_floor = 0.2f
			},
			.light = {
					.x = 0.0f,
					.y = 0.0f,
					.color = al_map_rgb_f(1.0f, 0.8f, 1.0f),
					.linear = 40.0f,
					.quadratic = 1.5f,
					.clamp = 5.0f
			},
			.world = context->scene->world,
			.jitter_falloff = 1.2f,
			.pulse_falloff = 1.5f,
			.fullness = gm_global_weapon_info[GM_WEAPON_EGG].cost + 5,
			.max_fullness = 70.0f,
			.itime = 2.0f,
			.weapon = GM_WEAPON_EGG,
			.weapons = 1,

			.oven = {
					.bx = 1360,
					.by = 175,
					.health = 500.0f,
					.max_health = 500.0f,
					.itime = 10.0f
			},

			.credits_timeout = -1.0f,

			.start = time(0)
	};

	al_grab_mouse(context->display->display);
	al_set_window_title(context->display->display, "Stuffed to the Brim-stone");

	gm_global_state.death = al_load_sample("res/snd/pdie.wav");
	if(!gm_global_state.death) {
		return PDN_LOG_RESULT_PATH(al_load_sample, "res/snd/pdie.wav", PDN_RESULT_ERROR);
	}

	gm_global_state.key_pick = al_load_sample("res/snd/key_pick.wav");
	gm_global_state.weapon_pick = al_load_sample("res/snd/weapon_pick.wav");
	gm_global_state.union_pick = al_load_sample("res/snd/union_pick.wav");

	gm_global_state.end_music = al_load_sample("res/snd/STDE2.wav");
	gm_global_state.main_music = al_load_sample("res/snd/kitch2.wav");
	al_play_sample(gm_global_state.main_music, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_LOOP, &gm_global_state.current);

	gm_global_state.width = (float) al_get_display_width(context->display->display);
	gm_global_state.height = (float) al_get_display_height(context->display->display);

	auto world = context->scene->world;

	ECS_COMPONENT_DEFINE(context->scene->world, gm_component_enemy_t);
	ECS_COMPONENT_DEFINE(context->scene->world, gm_component_physics_t);
	ECS_COMPONENT_DEFINE(context->scene->world, gm_component_projectile_t);
	ECS_COMPONENT_DEFINE(context->scene->world, gm_component_sprite_aux_t);
	ECS_COMPONENT_DEFINE(context->scene->world, gm_component_pickup_t);

	ECS_SYSTEM_DEFINE(
			world, gm_render_tilemap, EcsOnUpdate,
			pdn_component_transform_t, pdn_component_tilemap_t);

	ECS_SYSTEM_DEFINE(
			world, gm_render_sprite, EcsOnUpdate,
			pdn_component_transform_t, pdn_component_sprite_t, gm_component_sprite_aux_t);

	ECS_SYSTEM_DEFINE(
			world, gm_update_physics, EcsOnUpdate,
			pdn_component_transform_t, gm_component_physics_t);

	ECS_SYSTEM_DEFINE(
			world, gm_update_enemy, EcsOnUpdate,
			pdn_component_transform_t, gm_component_enemy_t, gm_component_physics_t, gm_component_sprite_aux_t);

	ECS_SYSTEM_DEFINE(
			world, gm_update_projectile, EcsOnUpdate,
			pdn_component_transform_t, gm_component_projectile_t, pdn_component_sprite_t, gm_component_sprite_aux_t, gm_component_physics_t);

	ECS_SYSTEM_DEFINE(
			world, gm_update_pickup, EcsOnUpdate,
			pdn_component_transform_t, gm_component_pickup_t);

	gm_global_state.full = al_load_bitmap("res/img/bar_full.png");
	gm_global_state.empty = al_load_bitmap("res/img/bar_empty.png");
	gm_global_state.reload_full = al_load_bitmap("res/img/reload_full.png");
	gm_global_state.reload_empty = al_load_bitmap("res/img/reload_empty.png");
	gm_global_state.marker = al_load_bitmap("res/img/marker.png");
	gm_global_state.pwmarker = al_load_bitmap("res/img/wpar.png");
	al_set_display_icon(context->display->display, gm_global_state.marker);

	gm_global_state.oven.bitmap = al_load_bitmap("res/img/oven.png");
	gm_global_state.oven.death = al_load_sample("res/snd/ovendie.wav");
	gm_global_state.oven.yow = al_load_sample("res/snd/yow.wav");

	gm_global_state.hit = al_load_sample("res/snd/hit_me.wav");

	ecs_entity_t test2 = ecs_entity(gm_global_state.world, { .name = "test2" });
	ecs_set(world, test2, pdn_component_transform_t, { 0.0f, 0.0f });
	struct pdn_tilemap tilemap;
	pdn_script_file_table(
			"res/map/k2.lua", pdn_tilemap_script_table_handler_patched,
			&tilemap);

	gm_global_state.map = tilemap;

	ecs_set(world, test2, pdn_component_tilemap_t, { tilemap });

	for(size_t i = 0; i < GM_PROJECTILE_COUNT; ++i) {
		auto proj = &gm_global_projectile_info[i];
		if(proj->sample_path) {
			proj->sample = al_load_sample(proj->sample_path);
		}
		if(proj->shhot_path) {
			proj->shhot = al_load_sample(proj->shhot_path);
		}
	}

	for(size_t i = 0; i < GM_ENEMY_COUNT; ++i) {
		auto en = &gm_global_enemy_info[i];
		if(!en->sample_path) continue;
		en->sample = al_load_sample(en->sample_path);
	}

	return PDN_RESULT_OK;
}
