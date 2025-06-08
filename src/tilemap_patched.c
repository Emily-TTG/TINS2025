// TODO: This is just using the easy-but-dumb solution of loading the tileset
//		 For every tilemap. In future should decouple these with a loaded
//		 Tileset registry with refcounts, hashing etc.
static enum pdn_result pdn_tileset_script_table_handler_patched(
		struct pdn_script* script, const char* path, void* pass) {

	struct pdn_tileset* out = pass;

	size_t in_length = (strrchr(path, '/') + 1) - path;

	char* image;
	size_t image_length;

	lua_getfield(script->state, -1, "image");
	{
		image_length = lua_strlen(script->state, -1);

		image = malloc(in_length + image_length + 1);
		strncpy(image, path, in_length);
		strcpy(image + in_length, lua_tostring(script->state, -1));
	}
	lua_pop(script->state, 1);

	out->atlas = al_load_bitmap(image);
	if(!out->atlas) {
		enum pdn_result result = PDN_LOG_RESULT_PATH(
				al_load_bitmap, image, PDN_RESULT_ERROR);

		free(image);
		return result;
	}

	free(image);

	out->dimension = pdn_script_table_get_int(script, -1, "tilewidth");
	out->width =
			pdn_script_table_get_int(script, -1, "imagewidth") / out->dimension;

	out->height =
			pdn_script_table_get_int(script, -1, "imageheight") / out->dimension;

	return PDN_RESULT_OK;
}

enum pdn_result pdn_tilemap_script_table_handler_patched(
		struct pdn_script* script, const char* path, void* pass) {

	enum pdn_result result;

	struct pdn_tilemap* out = pass;

	char* tileset;

	out->width = pdn_script_table_get_int(script, -1, "width");
	out->height = pdn_script_table_get_int(script, -1, "height");
	int length = out->width * out->height;

	lua_getfield(script->state, -1, "layers");
	{
		out->layers = (int) lua_objlen(script->state, -1);
		out->data = calloc(out->layers, sizeof(int*));

		for(int i = 0; i < out->layers; ++i) {
			bool tile = false;
			lua_rawgeti(script->state, -1, i + 1);
			{
				lua_getfield(script->state, -1, "type");
				{
					if(lua_tostring(script->state, -1)[0] == 't') {
						tile = true;
					}
				}
				lua_pop(script->state, 1);

				if(tile) {
					lua_getfield(script->state, -1, "data");
					{
						out->data[i] = malloc(length * sizeof(int));

						for(int j = 0; j < length; ++j) {
							lua_rawgeti(script->state, -1, j + 1);
							{
								out->data[i][j] =
										(int) lua_tointeger(script->state, -1);
							}
							lua_pop(script->state, 1);
						}
					}
					lua_pop(script->state, 1);
				}
				else {
					lua_getfield(script->state, -1, "objects");
					{
						size_t n_objects = lua_objlen(script->state, -1);
						for(int j = 0; j < n_objects; ++j) {
							lua_rawgeti(script->state, -1, j + 1);
							{
								auto world = gm_global_state.world;
								const char* name = pdn_script_table_get_string(script, -1, "name");
								ecs_entity_t test = ecs_entity(
										world,
										{});

								if(!strcmp(name, "player")) {
									gm_global_state.player = test;
								}
								else if(name[0] == 'd') { // enemy
									gm_global_state.nenemies++;
									enum gm_enemy_type type = name[1] - '0';
									ecs_set(
											world, test, gm_component_enemy_t,
											{
												.type = type,
												.health = gm_global_enemy_info[type].health
											});

									ecs_set(
											world, test, gm_component_physics_t,
											{
												.dampening = gm_global_enemy_info[type].dampening
											});
								}
								else if(name[0] == 'w') { // weapon
									ecs_set(world, test, gm_component_pickup_t,
											{ .type = GM_WEAPON, .weapon = name[1] - '0' });
								}
								else if(name[0] == 'k') { // key
									gm_global_state.nkeys++;
									ecs_set(world, test, gm_component_pickup_t,
											{ .type = GM_KEY });
								}
								else if(name[0] == 's') { // weapon shop
									ecs_set(world, test, gm_component_pickup_t,
											{ .type = GM_WEAPON, .weapon = name[1] - '0', .price = (name[2] - '0') * 2.0f });
								}
								else if(name[0] == 'v') { // key shop
									gm_global_state.nkeys++;
									ecs_set(world, test, gm_component_pickup_t,
											{ .type = GM_KEY, .price = (name[1] - '0') * 2.0f });
								}
								else if(name[0] == 'u') { // union
									ecs_set(world, test, gm_component_pickup_t,
											{ .type = GM_UNION });
								}

								ecs_set(
										world, test, pdn_component_transform_t,
										{
											.x = (float) pdn_script_table_get_int(script, -1, "x"),
											.y = (float) pdn_script_table_get_int(script, -1, "y") - 16
										});

								ecs_set(
										world, test, pdn_component_sprite_t,
										{
											.tid = pdn_script_table_get_int(script, -1, "gid")
										});

								ecs_set(
										world, test, gm_component_sprite_aux_t,
										{});
							}

							lua_pop(script->state, 1);
						}
					}
					lua_pop(script->state, 1);
				}
			}
			lua_pop(script->state, 1);
		}
	}
	lua_pop(script->state, 1);

	lua_getfield(script->state, -1, "tilesets");
	{
		lua_rawgeti(script->state, -1, 1);
		{
			lua_getfield(script->state, -1, "filename");
			{
				static const char relative[] = "../";
				static const char extension[] = "lua";

				const char* tileset_path = lua_tostring(script->state, -1);
				char* split = strrchr(tileset_path, '/') + 1;
				char* extension_split = strchr(split, '.') + 1;

				size_t in_path_length = (strrchr(path, '/') + 1) - path;
				size_t path_length = split - tileset_path;
				size_t file_length = extension_split - split;

				size_t total_length =
						in_path_length + path_length + (sizeof(relative) - 1)
						+ file_length + (sizeof(extension) - 1) + 1;

				tileset = malloc(total_length);
				tileset[0] = 0;

				// I know str[n]cat is suboptimal here as we have the lengths
				// But this makes the code substantially more readable without
				// Making any real meaningful impact on performance.
				strncat(tileset, path, in_path_length);
				strncat(tileset, tileset_path, path_length);
				strcat(tileset, relative);
				strncat(tileset, split, file_length);
				strcat(tileset, extension);
			}
			lua_pop(script->state, 1);
		}
		lua_pop(script->state, 1);
	}
	lua_pop(script->state, 1);

	result = pdn_script_file_table(
			tileset, pdn_tileset_script_table_handler, &out->tileset);

	gm_global_state.object_tileset = out->tileset;

	if(result) {
		(void) PDN_LOG_RESULT_PATH(
				pdn_script_file_table(pdn_tileset_script_table_handler), tileset,
				result);

		free(out->data);
		free(tileset);
		return result;
	}

	free(tileset);

	return PDN_RESULT_OK;
}
