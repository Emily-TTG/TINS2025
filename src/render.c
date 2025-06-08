
void gm_render_tilemap(ecs_iter_t* it) {
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
			if(!layer_buffer) continue;

			for(int y = 0; y < tilemap->tilemap.height; ++y) {
				for(int x = 0; x < tilemap->tilemap.width; ++x) {
					float sw = (float) dimension;
					float sh = (float) dimension;

					static const int adjust = 0;
					float tx = (float) (x * (dimension - adjust)) * zoom;
					float ty = (float) (y * (dimension - adjust)) * zoom;

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

					if(dx < -(float) dimension || dx > gm_global_state.width + (float) dimension) {
						continue;
					}
					if(dy < -(float) dimension || dy > gm_global_state.height + (float) dimension) {
						continue;
					}

					int index = y * tilemap->tilemap.width + x;
					int global_id = layer_buffer[index];

					bool horizontal = global_id & (1 << 31);
					bool vertical = global_id & (1 << 30);

					int id = (global_id & 0xFFFFFFF) - 1;
					int tile_column = id % tileset->width;
					int tile_row = id / tileset->width;

					float sx = (float) (tile_column * dimension);
					float sy = (float) (tile_row * dimension) - 1.0f;

					int flags = 0;
					if(horizontal) {
						flags |= ALLEGRO_FLIP_HORIZONTAL;
					}
					else if(vertical) {
						flags |= ALLEGRO_FLIP_VERTICAL;
					}

					float dl = gm_light_attenuate(light, camera, dx, dy);
					if(dl > camera->light_floor) {
						al_draw_tinted_scaled_rotated_bitmap_region(
								tileset->atlas, sx, sy, sw, sh,
								gm_color_add_color(
										gm_color_multiply(light->color, dl),
										gm_color_multiply(
												gm_color_random(),
												camera->color_pulse)),
								cx, cy, dx, dy, zoom + 0.01f, zoom + 0.01f,
								0.0f, flags);
					}
				}
			}
		}
	}
}

void gm_render_sprite(ecs_iter_t* it) {
	auto transforms = ecs_field(it, pdn_component_transform_t, 0);
	auto sprites = ecs_field(it, pdn_component_sprite_t, 1);
	auto aux_s = ecs_field(it, gm_component_sprite_aux_t, 2);

	auto camera = &gm_global_state.camera;
	float zoom = camera->zoom;

	auto light = &gm_global_state.light;

	auto tileset = gm_global_state.object_tileset;
	int dimension = tileset.dimension;

	for(int i = 0; i < it->count; ++i) {
		auto transform = &transforms[i];
		auto sprite = &sprites[i];
		auto aux = &aux_s[i];

		int id = (sprite->tid & 0xFFFFFFF) - 1;
		int tile_column = id % tileset.width;
		int tile_row = id / tileset.width;

		float sx = (float) (tile_column * dimension);
		float sy = (float) (tile_row * dimension);

		float sw = (float) dimension;
		float sh = (float) dimension;

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
					tileset.atlas, sx, sy, sw, sh,
					gm_color_sub_color(
							gm_color_add_color(
								gm_color_multiply(light->color, dl),
								gm_color_multiply(
										gm_color_random(),
										camera->color_pulse)),
							aux->invtint),
					cx, cy, dx, dy, zoom + aux->ex_scale, zoom + aux->ex_scale, 0.0f, aux->flip ? ALLEGRO_FLIP_HORIZONTAL : 0);
		}
	}
}
