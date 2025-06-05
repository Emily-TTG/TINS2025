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

#include <stdlib.h>
#include <time.h>
#include <math.h>

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

static struct gm_state {
	struct gm_camera camera;
	struct gm_light light;
} gm_global_state;

// Position is pre-scaled.
static float gm_light_attenuate(
		struct gm_light* light, struct gm_camera* camera, float x, float y) {

	float light_x = (light->x * camera->zoom) - camera->x;
	float light_y = (light->y * camera->zoom) - camera->y;
	al_draw_circle(light_x, light_y, 5.0f, light->color, 5.0f);

	float dxl = fabsf(x - light_x);
	float dyl = fabsf(y - light_y);
	float linear = (light->linear * camera->zoom) / (dxl + dyl);
	float quadratic = (light->quadratic * camera->zoom) / sqrtf(dxl + dxl + dyl + dyl);

	float dl = linear + quadratic;
	return roundf(dl * light->clamp) / light->clamp;
}

static float gm_random(void) {
	return (float) rand() / (float) RAND_MAX;
}

static float gm_sign_random(void) {
	return ((float) rand() / (float) RAND_MAX) - 0.5f;
}

static ALLEGRO_COLOR gm_color_multiply(ALLEGRO_COLOR color, float value) {
	return al_map_rgb_f(color.r * value, color.g * value, color.b * value);
}

static ALLEGRO_COLOR gm_color_add_color(
		ALLEGRO_COLOR color, ALLEGRO_COLOR other) {

	return al_map_rgb_f(
			color.r + other.r, color.g + other.g, color.b + other.b);
}

static ALLEGRO_COLOR gm_color_random() {
	return al_map_rgb_f(gm_random(), gm_random(), gm_random());
}

static ALLEGRO_COLOR gm_color_multiply_color(
		ALLEGRO_COLOR color, ALLEGRO_COLOR other) {

	return al_map_rgb_f(
			color.r * other.r, color.g * other.g, color.b * other.b);
}

ECS_SYSTEM_DECLARE(gm_render_tilemap);
ECS_SYSTEM_DECLARE(gm_render_sprite);

static void gm_render_tilemap(ecs_iter_t* it) {
	auto transforms = ecs_field(it, pdn_component_transform_t, 0);
	auto tilemaps = ecs_field(it, pdn_component_tilemap_t, 1);

	auto camera = &gm_global_state.camera;
	float zoom = camera->zoom;

	auto light = &gm_global_state.light;

	for(int i = 0; i < it->count; ++i) {
		auto transform = &transforms[i];
		auto tilemap = &tilemaps[i];

		auto tileset = &tilemap->tilemap.tileset;
		int dimension = tileset->dimension;

		for(int layer = 0; layer < tilemap->tilemap.layers; ++layer) {
			int* layer_buffer = tilemap->tilemap.data[layer];

			for(int y = 0; y < tilemap->tilemap.height; ++y) {
				for(int x = 0; x < tilemap->tilemap.width; ++x) {
					int index = y * tilemap->tilemap.width + x;
					int global_id = layer_buffer[index];

					bool horizontal = global_id & (1 << 31);
					bool vertical = global_id & (1 << 30);

					int id = (global_id & 0xFFFFFFF) - 1;
					int tile_column = id % tileset->width;
					int tile_row = id / tileset->width;

					float sx = (float) (tile_column * dimension);
					float sy = (float) (tile_row * dimension);
					float sw = (float) dimension;
					float sh = (float) dimension;

					static const int adjust = 1;
					float tx = (float) (x * (dimension - adjust)) * zoom;
					float ty = (float) (y * (dimension - adjust)) * zoom;

					int flags = 0;
					if(horizontal) {
						flags |= ALLEGRO_FLIP_HORIZONTAL;
					}
					else if(vertical) {
						flags |= ALLEGRO_FLIP_VERTICAL;
					}

					float cx = sw / 2.0f;
					float cy = sh / 2.0f;

					float cx_scaled = cx * zoom;
					float cy_scaled = cy * zoom;

					float dx =
							transform->x + tx - camera->x + cx_scaled +
							(gm_sign_random() * camera->jitter);

					float dy =
							transform->y + ty - camera->y + cy_scaled +
							(gm_sign_random() * camera->jitter);

					float dl = gm_light_attenuate(light, camera, dx, dy);
					if(dl > camera->light_floor) {
						al_draw_tinted_scaled_rotated_bitmap_region(
								tileset->atlas, sx, sy, sw, sh,
								gm_color_add_color(
										gm_color_multiply(light->color, dl),
										gm_color_multiply(
												gm_color_random(),
												camera->color_pulse)),
								cx, cy, dx, dy, zoom + 0.05f, zoom + 0.05f,
								0.0f, flags);
					}

				}
			}
		}
	}
}

static void gm_render_sprite(ecs_iter_t* it) {
	auto transforms = ecs_field(it, pdn_component_transform_t, 0);
	auto sprites = ecs_field(it, pdn_component_sprite_t, 1);

	auto camera = &gm_global_state.camera;
	float zoom = camera->zoom;

	auto light = &gm_global_state.light;

	for(int i = 0; i < it->count; ++i) {
		auto transform = &transforms[i];
		auto sprite = &sprites[i];

		float sw = (float) al_get_bitmap_width(sprite->bitmap);
		float sh = (float) al_get_bitmap_height(sprite->bitmap);

		float cx = sw / 2.0f;
		float cy = sh / 2.0f;

		float dx =
				((transform->x + cx) * zoom) - camera->x +
				(gm_sign_random() * camera->jitter);

		float dy =
				((transform->y + cy) * zoom) - camera->y +
				(gm_sign_random() * camera->jitter);


		float dl = gm_light_attenuate(light, camera, dx, dy);
		if(dl > camera->light_floor) {
			al_draw_tinted_scaled_rotated_bitmap_region(
					sprite->bitmap, 0.0f, 0.0f, sw, sh,
					gm_color_add_color(
							gm_color_multiply(light->color, dl),
							gm_color_multiply(
									gm_color_random(), camera->color_pulse)),
					cx, cy, dx, dy, zoom, zoom, 0.0f, 0);
		}
	}
}

enum pdn_result pdn_local_start(struct pdn_context* context) {
	srand(time(0));

	gm_global_state = (struct gm_state) {
			.camera = {
					.x = 0.0f,
					.y = 0.0f,
					.zoom = 1.0f,
					.jitter = 0.0f,
					.light_floor = 0.2f
			},
			.light = {
					.x = 100.0f,
					.y = 100.0f,
					.color = al_map_rgb_f(1.0f, 0.8f, 1.0f),
					.linear = 40.0f,
					.quadratic = 1.5f,
					.clamp = 5.0f
			}
	};

	auto world = context->scene->world;

	ECS_SYSTEM_DEFINE(
			world, gm_render_tilemap, EcsOnUpdate,
			pdn_component_transform_t, pdn_component_tilemap_t);

	ECS_SYSTEM_DEFINE(
			world, gm_render_sprite, EcsOnUpdate,
			pdn_component_transform_t, pdn_component_sprite_t);

	//ecs_entity_t test = ecs_entity(world, { .name = "test" });
	//ecs_set(world, test, pdn_component_transform_t, { 50.0f, 50.0f });
	//ecs_set(
	//		world, test, pdn_component_sprite_t,
	//		{ al_load_bitmap("res/img/arse.png") });

	ecs_entity_t test2 = ecs_entity(world, { .name = "test2" });
	ecs_set(world, test2, pdn_component_transform_t, { 0.0f, 0.0f });
	struct pdn_tilemap tilemap;
	pdn_script_file_table(
			"res/map/map.lua", pdn_tilemap_script_table_handler, &tilemap);

	ecs_set(world, test2, pdn_component_tilemap_t, { tilemap });

	return PDN_RESULT_OK;
}

enum pdn_result pdn_local_update(struct pdn_context* context, double delta) {
	auto ui = context->ui;

	al_set_target_backbuffer(context->display->display);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	ALLEGRO_KEYBOARD_STATE keyboard;
	al_get_keyboard_state(&keyboard);

	float speed = 5.0f;
	float zoom_speed = 0.05f;
	if(al_key_down(&keyboard, ALLEGRO_KEY_W)) {
		gm_global_state.camera.y -= speed;
	}
	if(al_key_down(&keyboard, ALLEGRO_KEY_S)) {
		gm_global_state.camera.y += speed;
	}
	if(al_key_down(&keyboard, ALLEGRO_KEY_A)) {
		gm_global_state.camera.x -= speed;
	}
	if(al_key_down(&keyboard, ALLEGRO_KEY_D)) {
		gm_global_state.camera.x += speed;
	}
	if(al_key_down(&keyboard, ALLEGRO_KEY_Q)) {
		gm_global_state.camera.zoom -= zoom_speed;
	}
	if(al_key_down(&keyboard, ALLEGRO_KEY_E)) {
		gm_global_state.camera.zoom += zoom_speed;
	}

	ecs_progress(context->scene->world, (float) delta);

	struct nk_rect area = nk_rect(50, 50, 220, 220);
	enum nk_panel_flags flags =
			NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_TITLE;

	if(nk_begin(ui->context, "game", area, flags)) {
		nk_layout_row_static(ui->context, 30, 180, 1);
		nk_property_float(
				ui->context, "linear",
				0.0f, &gm_global_state.light.linear, 100.0f, 0.1f, 0.1f);

		nk_property_float(
				ui->context, "quadratic",
				0.0f, &gm_global_state.light.quadratic, 100.0f, 0.1f, 0.1f);

		nk_property_float(
				ui->context, "clamp",
				0.0f, &gm_global_state.light.clamp, 100.0f, 1.00f, 1.00f);

		nk_property_float(
				ui->context, "jitter",
				0.0f, &gm_global_state.camera.jitter, 100.0f, 0.1f, 0.1f);

		nk_property_float(
				ui->context, "color pulse",
				0.0f, &gm_global_state.camera.color_pulse, 1.0f, 0.01f, 0.01f);

		nk_property_float(
				ui->context, "light floor",
				0.0f, &gm_global_state.camera.light_floor, 1.0f, 0.01f, 0.01f);
	}
	nk_end(ui->context);

	return PDN_RESULT_OK;
}
