struct gm_weapon_info gm_global_weapon_info[GM_WEAPON_COUNT] = {
		[GM_WEAPON_EGG] = {
				.name = "Egg",
				.cost = 15.0f,
				.projectile = GM_EGG2,
				.damage = 6.0f,
				.knockback = 12.0f,
				.owned = true
		},
		[GM_WHISK] = {
				.name = "Whisk",
				.radius = 32.0f,
				.damage = 3.0f,
				.knockback = 10.0f,
				.melee = true,
				.cost = 0.0f
		},
		[GM_WEAPON_SALT] = {
				.name = "Salt",
				.cost = 0.5f,
				.projectile = GM_SALT,
				.damage = 1.0f,
				.knockback = 4.0f,
		},
		[GM_WEAPON_PEPPER] = {
				.name = "Pepper",
				.cost = 1.0f,
				.projectile = GM_PEPPER,
				.damage = 3.0f,
				.knockback = 5.0f
		},
		[GM_WEAPON_BURNER] = {
				.name = "Burner",
				.cost = 24.0f,
				.projectile = GM_FLAME,
				.damage = 12.0f,
				.knockback = 8.0f
		},
		[GM_WEAPON_SAP] = {
				.name = "Salt & Pepper",
				.cost = 1.5f,
				.projectile = GM_SAP,
				.damage = 4.0f,
				.knockback = 7.0f
		}
};

struct gm_enemy_info gm_global_enemy_info[GM_ENEMY_COUNT] = {
		[GM_DEMON_0] = {
				.name = "Burgelzebub",
				.health = 10.0f,
				.dampening = 0.8f,
				.width_mul = 3.0f,
				.projectile = GM_BURGER,
				.follow_force = 0.3f,
				.force_cap = 0.2f,
				.follow_distance = 16.0f * 15.0f,
				.min_distance = 16.0f * 6.0f,
				.sample_path = "res/snd/owie.wav",
				.itime = 2.0f,
				.cash = 3,
				.tid = 43
		},
		[GM_DEMON_1] = {
				.name = "Batterhomet",
				.health = 15.0f,
				.dampening = 0.9f,
				.width_mul = 3.5f,
				.projectile = GM_BREADCRUMB,
				.follow_force = 0.5f,
				.force_cap = 0.3f,
				.follow_distance = 16.0f * 10.0f,
				.min_distance = 16.0f * 4.0f,
				.sample_path = "res/snd/owie.wav",
				.itime = 2.0f,
				.cash = 1,
				.tid = 63
		},
		[GM_DEMON_2] = {
				.name = "Egg Deviller",
				.health = 25.0f,
				.dampening = 0.7f,
				.width_mul = 4.5f,
				.projectile = GM_EGG,
				.follow_force = 0.2f,
				.force_cap = 0.2f,
				.follow_distance = 16.0f * 18.0f,
				.min_distance = 16.0f * 7.0f,
				.sample_path = "res/snd/owie.wav",
				.itime = 2.0f,
				.cash = 5,
				.tid = 83
		},
		[GM_DEMON_3] = {
				.name = "Al Dante",
				.health = 100.0f,
				.dampening = 0.8f,
				.width_mul = 3.5f,
				.projectile = GM_FLAME,
				.follow_force = 0.1f,
				.force_cap = 0.4f,
				.follow_distance = 16.0f * 20.0f,
				.min_distance = 16.0f * 2.0f,
				.sample_path = "res/snd/owie.wav",
				.itime = 2.0f,
				.cash = 15,
				.tid = 127
		}
};

struct gm_projectile_info gm_global_projectile_info[GM_PROJECTILE_COUNT] = {
		[GM_NONE] = {
				.reload = INFINITY
		},
		[GM_BURGER] = {
				.name = "Burger",
				.reload = 7.0f,
				.damage = 16.0f,
				.force = 2.0f,
				.tid = GM_PROJECTILE_BASE + 1,
				.animate_time = 1.0f,
				.lifetime = 15.0f,
				.sample_path = "res/snd/nom.wav",
				.radius = 20.0f,
				.shhot_path = "res/snd/explosion.wav"
		},
		[GM_ANGEL] = {
				.name = "Angel",
				.reload = INFINITY,
				.force = 1.0f,
				.tid = GM_PROJECTILE_BASE + 2,
				.animate_time = 0.8f,
				.lifetime = 5.0f,
				.sample_path = "res/snd/sparkle.wav"
		},
		[GM_BREADCRUMB] = {
				.name = "Breadcrumb",
				.reload = 2.0f,
				.burst = 3,
				.burst_interval = 1.0f,
				.damage = 8.0f,
				.force = 2.0f,
				.tid = GM_PROJECTILE_BASE + 3,
				.animate_time = INFINITY,
				.lifetime = 10.0f,
				.radius = 8.0f,
				.shhot_path = "res/snd/click.wav",
		},
		[GM_EGG] = {
				.name = "Egg",
				.reload = 10.0f,
				.damage = 19.0f,
				.force = 0.5f,
				.tid = GM_PROJECTILE_BASE + 4,
				.animate_time = INFINITY,
				.lifetime = 15.0f,
				.radius = 15.0f,
				.growth = 0.05f,
				.shhot_path = "res/snd/chunk.wav"
		},
		[GM_EGG2] = {
				.name = "Egg",
				.reload = 5.0f,
				.damage = 26.0f,
				.force = 0.7f,
				.tid = GM_WEAPON_BASE + 1,
				.animate_time = INFINITY,
				.lifetime = 7.0f,
				.radius = 15.0f,
				.growth = 0.03f,
				.shhot_path = "res/snd/chunk.wav"
		},
		[GM_SALT] = {
				.name = "Salt",
				.reload = 1.5f,
				.force = 1.2f,
				.damage = 2.0f,
				.tid = GM_PROJECTILE_BASE + 5,
				.animate_time = INFINITY,
				.lifetime = 4.0f,
				.radius = 15.0f,
				.growth = 0.01f,
				.shhot_path = "res/snd/random.wav"
		},
		[GM_PEPPER] = {
				.name = "Pepper",
				.reload = 1.5f,
				.force = 1.8f,
				.damage = 3.0f,
				.tid = GM_PROJECTILE_BASE + 6,
				.animate_time = INFINITY,
				.lifetime = 6.0f,
				.radius = 15.0f,
				.growth = 0.0f,
				.shhot_path = "res/snd/sneez.wav"
		},
		[GM_FLAME] = {
				.name = "Flame",
				.reload = 5.0f,
				.burst = 5,
				.burst_interval = 2.0f,
				.damage = 14.0f,
				.force = 1.1f,
				.tid = GM_PROJECTILE_BASE + 7,
				.animate_time = INFINITY,
				.lifetime = 12.0f,
				.radius = 15.0f,
				.growth = 0.02f,
				.shhot_path = "res/snd/fire.wav"
		},
		[GM_SAP] = {
				.name = "Salt & Pepper",
				.reload = 1.4f,
				.force = 1.9f,
				.damage = 4.0f,
				.tid = GM_PROJECTILE_BASE + 8,
				.animate_time = INFINITY,
				.lifetime = 7.0f,
				.radius = 14.0f,
				.growth = 0.08f,
				.shhot_path = "res/snd/sneez.wav"
		}
};

static void gm_spawn_projectile(float vx, float vy, float x, float y, enum gm_projectile_type type, bool player) {
	struct gm_projectile_info* projectile = &gm_global_projectile_info[type];

	ecs_entity_t test2 = ecs_entity(gm_global_state.world, {});
	ecs_set(gm_global_state.world, test2, pdn_component_transform_t, { x, y });
	ecs_set(gm_global_state.world, test2, gm_component_sprite_t, { .tid = projectile->tid });
	ecs_set(gm_global_state.world, test2, gm_component_sprite_aux_t, { .flip = vx < 0.0f });
	ecs_set(
			gm_global_state.world, test2, gm_component_physics_t,
			{
				.vx = vx,
				.vy = vy,
				.dampening = 1.0f
			});

	ecs_set(
			gm_global_state.world, test2, gm_component_projectile_t,
			{
				.type = type,
				.alt_tid = projectile->tid + 20,
				.player = player
			});

	if(projectile->shhot) {
		al_play_sample(projectile->shhot, 1.0f, 0.0f, (gm_sign_random() * 0.25f) + 0.75f, ALLEGRO_PLAYMODE_ONCE, 0);
	}
}

#define GM_GAIN(edl) GM_MIN(5000.0f / ((edl) * (edl)), 0.5f)

static bool gm_hit_enemy(gm_component_enemy_t* enemy, pdn_component_transform_t* transform, gm_component_physics_t* physics, enum gm_weapon weapon, float edl) {
	auto info = &gm_global_enemy_info[enemy->type];
	auto winfo = &gm_global_weapon_info[weapon];

	if(enemy->time_since_hit <= info->itime) return false;
	enemy->time_since_hit = 0.0f;

	al_play_sample(info->sample, GM_GAIN(edl), 0.0f, (gm_random() / 2.0f) + 0.75f, ALLEGRO_PLAYMODE_ONCE, 0);

	enemy->health -= winfo->damage;
	if(enemy->health <= 0.0f) {
		gm_spawn_projectile(0.0f, -1.0f, transform->x, transform->y, GM_ANGEL, false);
		gm_global_state.money += info->cash;
		gm_global_state.enemies++;
		return true;
	}
	else {
		physics->vx += gm_global_state.wdx * winfo->knockback;
		physics->vy += gm_global_state.wdy * winfo->knockback;
	}

	return false;
}

void gm_update_enemy(ecs_iter_t* it) {
	auto transforms = ecs_field(it, pdn_component_transform_t, 0);
	auto enemies = ecs_field(it, gm_component_enemy_t, 1);
	auto physics_s = ecs_field(it, gm_component_physics_t, 2);
	auto aux_s = ecs_field(it, gm_component_sprite_aux_t, 3);

	auto camera = &gm_global_state.camera;

	auto player_transf = ecs_get_mut(gm_global_state.world, gm_global_state.player, pdn_component_transform_t);

	for(int i = 0; i < it->count; ++i) {
		auto transform = &transforms[i];
		auto enemy = &enemies[i];
		auto physics = &physics_s[i];
		auto aux = &aux_s[i];

		auto info = &gm_global_enemy_info[enemy->type];

		bool was_hit = false;
		enemy->time_since_hit += 0.1f;

		if(enemy->time_since_hit <= info->itime) aux->invtint = al_map_rgb_f(0.0f, 1.0f, 1.0f);
		else aux->invtint = al_map_rgb_f(0.0f, 0.0f, 0.0f);

		float x = ((transform->x + 8) * camera->zoom) - camera->x;
		float y = ((transform->y + 8) * camera->zoom) - camera->y;

		float px = (player_transf->x + 8) * camera->zoom - camera->x;
		float py = (player_transf->y + 8) * camera->zoom - camera->y;

		float edx = px - x;
		float edy = py - y;
		float edl = sqrtf(edx * edx + edy * edy);
		if(edl <= info->follow_distance * camera->zoom) {
			if(edl > info->min_distance * camera->zoom) {
				float vx = physics->vx;
				float vy = physics->vy;
				vx += ((edx / edl) + (cosf(enemy->since_fired) * gm_random() * 4.0f)) * info->follow_force;
				vy += ((edy / edl) + (sinf(enemy->since_fired) * gm_random() * 4.0f)) * info->follow_force;

				if(vx >= info->force_cap) vx = info->force_cap;
				if(vx <= -info->force_cap) vx = -info->force_cap;
				if(vy >= info->force_cap) vy = info->force_cap;
				if(vy <= -info->force_cap) vy = -info->force_cap;

				physics->vx = vx;
				physics->vy = vy;
			}

			auto projectile = gm_global_projectile_info[info->projectile];
			enemy->since_fired += 0.1f * gm_random();

			if((enemy->since_fired >= projectile.reload) ||
				(enemy->burst && enemy->burst < projectile.burst && enemy->since_fired >= projectile.burst_interval)) {

				enemy->since_fired = 0.0f;

				if(++enemy->burst >= projectile.burst) {
					enemy->burst = 0;
				}

				gm_spawn_projectile((edx / edl) * projectile.force, (edy / edl) * projectile.force, transform->x, transform->y, info->projectile, false);
			}
		}

		auto weapon = &gm_global_weapon_info[gm_global_state.weapon];

		if(weapon->melee) {
			float wx = (gm_global_state.w_x + (gm_global_state.wdx * 8 * camera->zoom));
			float wy = (gm_global_state.w_y + (gm_global_state.wdy * 8 * camera->zoom));

			//al_draw_circle(wx, wy, weapon->radius, al_map_rgb_f(1.0f, 0.0f, 0.0f), 4.0f);

			float dx = x - wx;
			float dy = y - wy;
			float dw = sqrtf(dx * dx + dy * dy);

			if(dw <= weapon->radius) {
				was_hit = true;
			}
		}

		if(enemy->health < info->health) {
			float perc = enemy->health / info->health;
			float wid = info->health * info->width_mul;
			al_draw_line(x - (wid / 2.0f), y + 18, x + (wid / 2.0f), y + 18, al_map_rgb_f(1.0f, 0.0f, 0.0f), 4.0f);
			al_draw_line(x - (wid / 2.0f), y + 18, x - (wid / 2.0f) + (perc * wid), y + 18, al_map_rgb_f(0.0f, 1.0f, 0.0f), 4.0f);
		}

		if(was_hit) {
			if(gm_hit_enemy(enemy, transform, physics, gm_global_state.weapon, edl)) ecs_delete(it->world, it->entities[i]);
		}

	}
}

void gm_update_physics(ecs_iter_t* it) {
	auto transforms = ecs_field(it, pdn_component_transform_t, 0);
	auto physics_s = ecs_field(it, gm_component_physics_t, 1);

	for(int i = 0; i < it->count; ++i) {
		auto transform = &transforms[i];
		auto physics = &physics_s[i];

		float nx = transform->x;
		float ny = transform->y;

		nx += physics->vx;
		ny += physics->vy;

		int addrx = ((int) ((nx + 8) / 16) + (int) ((transform->y + 8) / 16) * gm_global_state.map.width);
		if(gm_global_state.map.data[1][addrx] || gm_global_state.map.data[3][addrx]) {
			nx = transform->x;
		}
		int addry = ((int) ((transform->x + 8) / 16) + (int) ((ny + 8) / 16) * gm_global_state.map.width);
		if(gm_global_state.map.data[1][addry] || gm_global_state.map.data[3][addry]) {
			ny = transform->y;
		}

		transform->x = nx;
		transform->y = ny;

		physics->vx *= physics->dampening;
		physics->vy *= physics->dampening;
	}
}

static void gm_hit_oven(float damage);


static void gm_delete_all(ecs_id_t component) {
	ecs_query_t* q = ecs_query(gm_global_state.world, { .terms = { { component } } });
	ecs_iter_t qit = ecs_query_iter(gm_global_state.world, q);
	while(ecs_query_next(&qit)) {
		for(size_t j = 0; j < qit.count; ++j) {
			ecs_delete(qit.world, qit.entities[j]);
		}
	}
	ecs_query_fini(q);
}
void gm_update_projectile(ecs_iter_t* it) {
	auto transforms = ecs_field(it, pdn_component_transform_t, 0);
	auto projectiles = ecs_field(it, gm_component_projectile_t, 1);
	auto sprites = ecs_field(it, gm_component_sprite_t, 2);
	auto aux_s = ecs_field(it, gm_component_sprite_aux_t, 3);
	auto physics_s = ecs_field(it, gm_component_physics_t, 4);

	auto camera = &gm_global_state.camera;

	auto player_transf = ecs_get_mut(gm_global_state.world, gm_global_state.player, pdn_component_transform_t);

	for(int i = 0; i < it->count; ++i) {
		auto transform = &transforms[i];
		auto projectile = &projectiles[i];
		auto sprite = &sprites[i];
		auto aux = &aux_s[i];
		auto physics = &physics_s[i];

		auto info = &gm_global_projectile_info[projectile->type];

		projectile->life += 0.1f;
		if(projectile->life >= info->lifetime) {
			ecs_delete(it->world, it->entities[i]);
			continue;
		}

		aux->ex_scale += info->growth;

		float radius = info->radius + (aux->ex_scale * 4);

		float x = ((transform->x + 8) * camera->zoom) - camera->x;
		float y = ((transform->y + 8) * camera->zoom) - camera->y;

		float px = (player_transf->x + 8) * camera->zoom - camera->x;
		float py = (player_transf->y + 8) * camera->zoom - camera->y;

		float edx = px - x;
		float edy = py - y;
		float edl = sqrtf(edx * edx + edy * edy);

		projectile->since_animate += 0.1f;
		if(projectile->since_animate >= info->animate_time) {
			projectile->since_animate = 0.0f;

			int tmp = sprite->tid;
			sprite->tid = projectile->alt_tid;
			projectile->alt_tid = tmp;

			if(sprite->tid > projectile->alt_tid) {
				static bool alternate = false;
				if(!alternate) {
					alternate = true;
					al_play_sample(info->sample, GM_GAIN(edl), 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, 0);
				}
				else alternate = false;
			}
		}

		if(info->damage < 1.0f) continue;

		//al_draw_circle(x, y, radius, al_map_rgb_f(1.0f, 0.0f, 0.0f), 4.0f);

		if(edl <= radius && gm_global_state.time_since_damage >= gm_global_state.itime && !projectile->player) {
			gm_global_state.time_since_damage = 0.0f;
			gm_global_state.fullness += info->damage;
			gm_global_state.camera.jitter += info->damage * 2.0f;

			float fullness = gm_global_state.fullness / gm_global_state.max_fullness;
			al_play_sample(gm_global_state.hit, 1.0f, 0.0f, (gm_random() / 2.0f) + (0.25f / fullness), ALLEGRO_PLAYMODE_ONCE, 0);

			if(gm_global_state.fullness > gm_global_state.max_fullness) {
				al_stop_sample(&gm_global_state.current);
				al_play_sample(gm_global_state.death, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, 0);

				gm_global_state.jitter_falloff = 1.01f;
				gm_global_state.pulse_falloff = 1.1f;
				gm_global_state.camera.jitter = 5.0f;
				gm_global_state.camera.color_pulse = 10.0f;

				gm_global_state.death_timeout = 1.0f;

				// TODO: Create save here.

				gm_delete_all(ecs_id(gm_component_enemy_t));
				gm_delete_all(ecs_id(gm_component_projectile_t));
			}

		}

		if(projectile->type == GM_FLAME) {
			int addr = ((int) ((transform->x + 8) / 16) + (int) ((transform->y + 8) / 16) * gm_global_state.map.width);
			if(gm_global_state.map.data[5][addr]) {
				gm_global_state.map.data[5][addr] = 0;
			}
		}

		if(projectile->player) {
			auto oven = &gm_global_state.oven;
			if(oven->spawned) {
				float dx = transform->x - oven->x;
				float dy = transform->y - oven->y;
				float dw = sqrtf(dx * dx + dy * dy);

				if(dw <= radius + 16) {
					gm_hit_oven(info->damage);
				}
			}

			ecs_query_t* q = ecs_query(gm_global_state.world, { .terms = {
					{ ecs_id(gm_component_enemy_t) },
					{ ecs_id(pdn_component_transform_t) },
					{ ecs_id(gm_component_physics_t) }
			} });

			ecs_iter_t qit = ecs_query_iter(gm_global_state.world, q);
			while(ecs_query_next(&qit)) {
				gm_component_enemy_t* en_s = ecs_field(&qit, gm_component_enemy_t, 0);
				pdn_component_transform_t* trs_s = ecs_field(&qit, pdn_component_transform_t, 1);
				gm_component_physics_t* phys_s = ecs_field(&qit, gm_component_physics_t, 2);

				for(size_t j = 0; j < qit.count; ++j) {
					gm_component_enemy_t* en = &en_s[j];
					pdn_component_transform_t* trs = &trs_s[j];
					gm_component_physics_t* phys = &phys_s[j];

					float dx = transform->x - trs->x;
					float dy = transform->y - trs->y;
					float dw = sqrtf(dx * dx + dy * dy);

					if(dw <= radius - 8) {
						if(gm_hit_enemy(en, transform, phys, gm_global_state.weapon, edl)) ecs_delete(qit.world, qit.entities[j]);
					}
				}
			}
			ecs_query_fini(q);
		}
	}
}

void gm_update_pickup(ecs_iter_t* it) {
	auto transforms = ecs_field(it, pdn_component_transform_t, 0);
	auto pickups = ecs_field(it, gm_component_pickup_t, 1);

	auto camera = &gm_global_state.camera;

	auto player_transf = ecs_get_mut(gm_global_state.world, gm_global_state.player, pdn_component_transform_t);

	for(int i = 0; i < it->count; ++i) {
		auto transform = &transforms[i];
		auto pickup = &pickups[i];

		if(al_key_down(&gm_global_state.keyboard, ALLEGRO_KEY_F)) {
			float x = ((transform->x + 8) * camera->zoom) - camera->x;
			float y = ((transform->y + 8) * camera->zoom) - camera->y;

			float px = (player_transf->x + 8) * camera->zoom - camera->x;
			float py = (player_transf->y + 8) * camera->zoom - camera->y;

			float edx = px - x;
			float edy = py - y;
			float edl = sqrtf(edx * edx + edy * edy);

			if(edl < 24.0f) {
				if(gm_global_state.money < pickup->price) continue;

				gm_global_state.money -= pickup->price;

				switch(pickup->type) {
					case GM_KEY: {
						gm_global_state.keys++;
						gm_global_state.tkeys++;
						al_play_sample(gm_global_state.key_pick, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, 0);
						break;
					}
					case GM_WEAPON: {
						gm_global_state.weapons += 1;
						gm_global_weapon_info[pickup->weapon].owned = true;
						gm_global_state.weapon = pickup->weapon;
						al_play_sample(gm_global_state.weapon_pick, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, 0);
						break;
					}
					case GM_UNION: {
						if(!gm_global_weapon_info[GM_WEAPON_SALT].owned || !gm_global_weapon_info[GM_WEAPON_PEPPER].owned) {
							continue;
						}
						gm_global_weapon_info[GM_WEAPON_SALT].owned = false;
						gm_global_weapon_info[GM_WEAPON_PEPPER].owned = false;
						gm_global_state.weapons += 1;
						gm_global_weapon_info[GM_WEAPON_SAP].owned = true;
						gm_global_state.weapon = GM_WEAPON_SAP;
						al_play_sample(gm_global_state.union_pick, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, 0);
						break;
					}
					default: break;
				}

				ecs_delete(it->world, it->entities[i]);
			}
		}
	}
}

static void gm_draw_money_tile(int tid, float xp, float oy) {
	al_draw_tinted_scaled_rotated_bitmap_region(
			gm_global_state.object_tileset.atlas,
			(float) (tid % gm_global_state.object_tileset.width) * 16,
			(float) (tid / gm_global_state.object_tileset.width) * 16,
			16, 16,
			al_map_rgb_f(1.0f, 1.0f, 1.0f),
			8, 8,
			xp,
			gm_global_state.height - (20 * gm_global_state.camera.zoom) - oy,
			gm_global_state.camera.zoom, gm_global_state.camera.zoom, 0, 0);
}

static void gm_spawn_minion(enum gm_enemy_type type) {
	auto oven = &gm_global_state.oven;
	auto world = gm_global_state.world;

	ecs_entity_t test = ecs_entity(world, {});

	ecs_set(world, test, gm_component_enemy_t,
			{
				.type = type,
				.health = gm_global_enemy_info[type].health
			});

	ecs_set(world, test, gm_component_physics_t,
			{
				.dampening = gm_global_enemy_info[type].dampening,
				.vy = gm_random() * 16.0f,
				.vx = gm_sign_random() * 10.0f
			});

	ecs_set(world, test, pdn_component_transform_t,
			{
				.x = oven->x,
				.y = oven->y
			});

	ecs_set(world, test, gm_component_sprite_t, { .tid = gm_global_enemy_info[type].tid });

	ecs_set(world, test, gm_component_sprite_aux_t, {});
}


static void gm_hit_oven(float damage) {
	auto oven = &gm_global_state.oven;

	if(oven->time_since_hit <= oven->itime) return;
	oven->time_since_hit = 0.0f;

	float ohperc = oven->health / oven->max_health;

	oven->health -= damage;
	al_play_sample(oven->yow, 2.0f, 0.0f, gm_sign_random() * 0.5f + 0.50f, ALLEGRO_PLAYMODE_ONCE, 0);

	if(oven->health <= 0.0f) {
		al_stop_sample(&gm_global_state.current);
		al_play_sample(oven->death, 1.0f, 0.0f, 1.0f, ALLEGRO_PLAYMODE_ONCE, 0);
		oven->spawned = false;
		gm_global_state.jitter_falloff = 1.01f;
		gm_global_state.pulse_falloff = 1.1f;
		gm_global_state.camera.jitter = 5.0f;
		gm_global_state.camera.color_pulse = 10.0f;

		gm_global_state.credits_timeout = 1.0f;

		gm_delete_all(ecs_id(gm_component_enemy_t));
		gm_delete_all(ecs_id(gm_component_projectile_t));
	}

	float hperc = oven->health / oven->max_health;

	if(ohperc > 0.9f && hperc <= 0.9f) {
		gm_spawn_minion(GM_DEMON_1);
		gm_spawn_minion(GM_DEMON_1);
		gm_spawn_minion(GM_DEMON_1);
	}

	if(ohperc > 0.7f && hperc <= 0.7f) {
		gm_spawn_minion(GM_DEMON_0);
		gm_spawn_minion(GM_DEMON_0);
		gm_spawn_minion(GM_DEMON_1);
	}

	if(ohperc > 0.4f && hperc <= 0.4f) {
		gm_spawn_minion(GM_DEMON_0);
		gm_spawn_minion(GM_DEMON_2);
	}

	if(ohperc > 0.1f && hperc <= 0.1f) {
		gm_spawn_minion(GM_DEMON_0);
		gm_spawn_minion(GM_DEMON_0);
		gm_spawn_minion(GM_DEMON_2);
	}
}

static void gm_spawn_oven(int addr) {
	auto oven = &gm_global_state.oven;

	oven->spawned = true;

	gm_global_state.map.data[1][addr + 198] = 164;
	gm_global_state.map.data[1][addr + 199] = 164;
	gm_global_state.map.data[1][addr + 200] = 164;
	gm_global_state.map.data[1][addr + 201] = 164;
	gm_global_state.map.data[1][addr + 202] = 164;
}

static void gm_do_oven() {
	auto oven = &gm_global_state.oven;
	auto camera = &gm_global_state.camera;

	if(!oven->spawned) return;

	oven->time_since_hit += 0.1f;

	float hperc = oven->health / oven->max_health;
	float iperc = 1.0f - hperc;
	oven->timer += 1.1f - hperc;
	float wooble = sinf(oven->timer / 5.0f) / 4.0f;
	float wooble2 = sinf(oven->timer / 10.0f);

	ALLEGRO_COLOR tint = oven->time_since_hit < oven->itime ? al_map_rgb_f(1.0f, 0.0f, 0.0f) : al_map_rgb_f(1.0f, 1.0f, 1.0f);

	float ox = (oven->x * camera->zoom) - camera->x;
	float oy = (oven->y * camera->zoom) - camera->y;

	al_draw_tinted_scaled_rotated_bitmap(
			oven->bitmap, tint, 24, 16, ox, oy,
			camera->zoom * 2.0f + (wooble - 0.5f),
			camera->zoom * 2.0f + (wooble - 0.5f),
			wooble, 0);

	float wid = oven->max_health / 2.0f;
	float yoff = 80;
	al_draw_line(ox - (wid / 2.0f), oy + yoff, ox + (wid / 2.0f), oy + yoff, al_map_rgb_f(1.0f, 0.0f, 0.0f), 8.0f);
	al_draw_line(ox - (wid / 2.0f), oy + yoff, ox - (wid / 2.0f) + (hperc * wid), oy + yoff, al_map_rgb_f(0.0f, 1.0f, 0.0f), 8.0f);

	oven->x = oven->bx + (wooble2 - 0.5f) * (16 * camera->zoom);
	oven->y = oven->by + (wooble2 - 0.5f) * (2 * camera->zoom);

	float x = ((oven->x + 8) * camera->zoom) - camera->x;
	float y = ((oven->y + 8) * camera->zoom) - camera->y;

	auto player_transf = ecs_get_mut(gm_global_state.world, gm_global_state.player, pdn_component_transform_t);

	float px = (player_transf->x + 8) * camera->zoom - camera->x;
	float py = (player_transf->y + 8) * camera->zoom - camera->y;

	float edx = px - x;
	float edy = py - y;
	float edl = sqrtf(edx * edx + edy * edy);

	if(gm_random() > 0.95 - (iperc * 0.015)) {
		auto breadcrumb = &gm_global_projectile_info[GM_BREADCRUMB];
		gm_spawn_projectile(
				(edx / edl) * breadcrumb->force, (edy / edl) * breadcrumb->force,
				oven->x, oven->y, GM_BREADCRUMB, false);
	}

	if(gm_random() > 0.995 - (iperc * 0.01)) {
		auto burger = &gm_global_projectile_info[GM_BURGER];
		gm_spawn_projectile(
				(edx / edl) * burger->force, (edy / edl) * burger->force,
				oven->x, oven->y, GM_BURGER, false);
	}

	if(gm_random() > 0.999 - (iperc * 0.002)) {
		auto egg = &gm_global_projectile_info[GM_EGG];
		gm_spawn_projectile(
				(edx / edl) * egg->force, (edy / edl) * egg->force,
				oven->x, oven->y, GM_EGG, false);
	}

	if(gm_random() > 0.9995 - (iperc * 0.0005)) {
		gm_spawn_minion(GM_DEMON_1);
	}
}

enum pdn_result pdn_local_update(struct pdn_context* context, double delta) {
	auto ui = context->ui;

	static struct timeval t = {};
	static bool first_ts = true;
	auto oldt = t;
	gettimeofday(&t, 0);
	if(!first_ts) {
		int64_t sdiff = t.tv_sec - oldt.tv_sec;
		int64_t udiff = (t.tv_usec + (sdiff * 1e6)) - oldt.tv_usec;
		usleep(GM_MAX(16666LL - udiff, 0LL));
	}
	first_ts = false;

	al_set_target_backbuffer(context->display->display);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	auto target = al_get_target_bitmap();
	gm_global_state.width = (float) al_get_bitmap_width(target);
	gm_global_state.height = (float) al_get_bitmap_height(target);

	al_get_keyboard_state(&gm_global_state.keyboard);

	auto player_transf = ecs_get_mut(gm_global_state.world, gm_global_state.player, pdn_component_transform_t);

	if(gm_global_state.credits_timeout > 0.0f && !gm_global_state.in_credits) {
		gm_global_state.credits_timeout += 0.1f;
		gm_global_state.light.quadratic -= 0.05f;
		if(gm_global_state.credits_timeout >= 30.0f) {
			al_play_sample(gm_global_state.end_music, 1.0f, 0.0f, 0.95f, ALLEGRO_PLAYMODE_ONCE, 0);
			player_transf->x = 176;
			player_transf->y = 96;
			gm_global_state.in_credits = true;
			gm_global_state.fullness = 0.0f;
			gm_global_state.camera.jitter = 0.0f;
			gm_global_state.camera.color_pulse = 0.0f;
		}
	}
	else if(gm_global_state.death_timeout > 0.0f) {
		gm_global_state.death_timeout += 0.1f;
		gm_global_state.light.quadratic -= 0.05f;
		if(gm_global_state.death_timeout >= 20.0f) {
			// TODO: Load here.
			exit(0);
		}
	}

	if(gm_global_state.in_credits || al_key_down(&gm_global_state.keyboard, ALLEGRO_KEY_O)) {
		if(gm_global_state.light.quadratic < 2.5f) {
			gm_global_state.light.quadratic += 0.1f;
		}
		player_transf->y += 0.12f;
		if(player_transf->y >= 20.9 * 16) {
			ALLEGRO_FILE* results = al_fopen("results.html", "w");
			al_fprintf(
					results,
"<html>"
"	<body>"
"		<h2><b>Time:</b> %ld</h2>"
"		<h2><b>Weapons:</b> %i/%i</h2>"
"		<h2><b>Enemies:</b> %i/%i</h2>"
"		<h2><b>Keys:</b> %i/%i</h2>"
"	</body>"
"</html>",
					time(0) - gm_global_state.start,
					gm_global_state.weapons, GM_WEAPON_COUNT,
					gm_global_state.enemies + 1, gm_global_state.nenemies + 1,
					gm_global_state.tkeys, gm_global_state.nkeys);

			exit(0);
		}
		ecs_progress(context->scene->world, (float) delta);

		gm_global_state.camera.x = (player_transf->x * gm_global_state.camera.zoom) - (gm_global_state.width / 2.0f);
		gm_global_state.camera.y = (player_transf->y * gm_global_state.camera.zoom) - (gm_global_state.height / 2.0f);

		gm_global_state.light.x = player_transf->x + 8;
		gm_global_state.light.y = player_transf->y + 8;
	}
	else {
		float speed = 1.0f;
		float nx = player_transf->x;
		gm_global_state.oldx = player_transf->x;
		float ny = player_transf->y;
		gm_global_state.oldy = player_transf->y;

		if(al_key_down(&gm_global_state.keyboard, ALLEGRO_KEY_W)) {
			ny -= speed;
		}
		if(al_key_down(&gm_global_state.keyboard, ALLEGRO_KEY_S)) {
			ny += speed;
		}
		if(al_key_down(&gm_global_state.keyboard, ALLEGRO_KEY_A)) {
			nx -= speed;
		}
		if(al_key_down(&gm_global_state.keyboard, ALLEGRO_KEY_D)) {
			nx += speed;
		}

		static bool was_q = false;
		if(al_key_down(&gm_global_state.keyboard, ALLEGRO_KEY_E)) {
			if(!was_q) {
				for(size_t w = 0; w < GM_WEAPON_COUNT; ++w) {
					enum gm_weapon we = (gm_global_state.weapon + w + 1) % GM_WEAPON_COUNT;
					if(gm_global_weapon_info[we].owned) {
						gm_global_state.weapon = we;
						break;
					}
				}
			}
			was_q = true;
		}
		else was_q = false;

		static bool was_e = false;
		if(al_key_down(&gm_global_state.keyboard, ALLEGRO_KEY_Q)) {
			if(!was_e) {
				for(size_t w = GM_WEAPON_COUNT; w > 0; --w) {
					enum gm_weapon we = (gm_global_state.weapon + w - 1) % GM_WEAPON_COUNT;
					if(gm_global_weapon_info[we].owned) {
						gm_global_state.weapon = we;
						break;
					}
				}
			}
			was_e = true;
		}
		else was_e = false;

		int addrx = ((int) ((nx + 8) / 16) + (int) ((player_transf->y + 8) / 16) * gm_global_state.map.width);
		if(gm_global_state.map.data[1][addrx] || gm_global_state.map.data[5][addrx]) {
			nx = player_transf->x;
		}
		int addry = ((int) ((player_transf->x + 8) / 16) + (int) ((ny + 8) / 16) * gm_global_state.map.width);
		if(gm_global_state.map.data[1][addry] || gm_global_state.map.data[5][addry]) {
			ny = player_transf->y;
		}

		if(gm_global_state.map.data[3][addrx]) {
			if(gm_global_state.keys > 0) {
				gm_global_state.keys--;
				gm_global_state.map.data[3][addrx] = 0;
			}
			else nx = player_transf->x;
		}
		if(gm_global_state.map.data[3][addry]) {
			if(gm_global_state.keys > 0) {
				gm_global_state.keys--;
				gm_global_state.map.data[3][addry] = 0;
			}
			else ny = player_transf->y;
		}

		if(gm_global_state.map.data[4][addrx]) {
			gm_spawn_oven(addrx);
			gm_global_state.map.data[4][addrx] = 0;
		}

		if(gm_global_state.map.data[4][addry]) {
			gm_spawn_oven(addry);
			gm_global_state.map.data[4][addry] = 0;
		}

		player_transf->x = nx;
		player_transf->y = ny;

		gm_global_state.camera.x = (player_transf->x * gm_global_state.camera.zoom) - (gm_global_state.width / 2.0f);
		gm_global_state.camera.y = (player_transf->y * gm_global_state.camera.zoom) - (gm_global_state.height / 2.0f);

		gm_global_state.light.x = player_transf->x + 8;
		gm_global_state.light.y = player_transf->y + 8;

		ALLEGRO_MOUSE_STATE m_state;
		al_get_mouse_state(&m_state);
		static bool held = false;
		bool didclick = false;

		if(m_state.buttons & 1) {
			if(!held) {
				didclick = true;
			}
			held = true;
		}
		else held = false;

		float px = (player_transf->x + 8) * gm_global_state.camera.zoom - gm_global_state.camera.x;
		float py = (player_transf->y + 8) * gm_global_state.camera.zoom - gm_global_state.camera.y;
		float a_dx = (float) m_state.x - px;
		float a_dy = (float) m_state.y - py;
		gm_global_state.aim = atanf(a_dy / a_dx);
		if(a_dx < 0.0f) gm_global_state.aim += 3.14f;

		auto winfo = &gm_global_weapon_info[gm_global_state.weapon];

		gm_global_state.wdx = cosf(gm_global_state.aim);
		gm_global_state.wdy = sinf(gm_global_state.aim);
		gm_global_state.w_x = px + ((winfo->melee ? 16.0f : 32.0f) * gm_global_state.wdx);
		gm_global_state.w_y = py + ((winfo->melee ? 16.0f : 32.0f) * gm_global_state.wdy);

	//	al_draw_line(px, py, px + (a_dx / a_len) * 16.0f, py + (a_dy / a_len) * 16.0f,
	//				 , 4.0f);
		ecs_progress(context->scene->world, (float) delta);

		int id = GM_WEAPON_BASE + gm_global_state.weapon;
		int tile_column = id % gm_global_state.object_tileset.width;
		int tile_row = id / gm_global_state.object_tileset.width;
		gm_global_state.time_since_fired += 0.1f;

		float sx = (float) (tile_column * 16);
		float sy = (float) (tile_row * 16);

		float wsw = (float) 16;
		float wsh = (float) 16;

		auto pinfo = &gm_global_projectile_info[winfo->projectile];

		al_draw_tinted_scaled_rotated_bitmap_region(
				gm_global_state.object_tileset.atlas, sx, sy, wsw, wsh,
				al_map_rgb_f(1.0f, 1.0f, 1.0f),
				winfo->melee ? 0 : 8, winfo->melee ? 16 : 8,
				gm_global_state.w_x, gm_global_state.w_y,
				gm_global_state.camera.zoom, gm_global_state.camera.zoom, gm_global_state.aim + (3.14f / (winfo->melee ? 4.0f : 2.0f)), 0);

		static float tried_no_food = -1.0f;
		float tried_no_food_max = 4.0f;

		if(!winfo->melee) {
			static float tried_p = -1.0f;

			if(didclick) {
				if(gm_global_state.time_since_fired >= pinfo->reload) {
					if(gm_global_state.fullness >= winfo->cost) {
						gm_global_state.time_since_fired = 0.0f;
						gm_global_state.fullness -= winfo->cost;

						gm_spawn_projectile(
								gm_global_state.wdx * pinfo->force, gm_global_state.wdy * pinfo->force,
								player_transf->x, player_transf->y, winfo->projectile, true);
					}
					else tried_no_food = 1.0f;
				}
				else tried_p = 1.0f;
			}

			float trymax = 4.0f;
			bool wtrying = tried_p > 0.0f;
			if(wtrying) {
				tried_p += 0.1f;
				if(tried_p > trymax) {
					tried_p = -1.0f;
				}
			}

			float reload_perc = gm_global_state.time_since_fired / pinfo->reload;
			if(reload_perc < 1.0f) {
				float width = wtrying ? 6 : 4;
				float offx = wtrying ? gm_sign_random() * width * (trymax - tried_p) : 0.0f;
				float offy = wtrying ? gm_sign_random() * width * (trymax - tried_p) : 0.0f;
				ALLEGRO_COLOR colw = wtrying ? al_map_rgb_f(1.0f, 0.0f, 0.0f) : al_map_rgb_f(1.0f, 1.0f, 1.0f);
				float sw = (float) al_get_bitmap_width(gm_global_state.reload_empty);
				float sh = (float) al_get_bitmap_height(gm_global_state.reload_empty);

				al_draw_tinted_scaled_bitmap(
						gm_global_state.reload_empty,
						colw,
						0, 0, sw, sh,
						80 + (gm_random() * gm_global_state.camera.jitter) + offx,
						(gm_global_state.height - 14 - sh - 4) + (gm_random() * gm_global_state.camera.jitter) + offy,
						sw * gm_global_state.camera.zoom, sh * gm_global_state.camera.zoom, 0);

				float dsw = sw * reload_perc;
				al_draw_tinted_scaled_bitmap(
						gm_global_state.reload_full,
						colw,
						0, 0, dsw, sh,
						80 + (gm_random() * gm_global_state.camera.jitter) + offx,
						(gm_global_state.height - 14 - sh - 4) + (gm_random() * gm_global_state.camera.jitter) + offy,
						dsw * gm_global_state.camera.zoom, sh * gm_global_state.camera.zoom, 0);
			}
		}

		gm_global_state.camera.jitter /= gm_global_state.jitter_falloff;
		gm_global_state.camera.color_pulse /= gm_global_state.pulse_falloff;

		gm_global_state.time_since_damage += 0.1f;

		bool ftrying = tried_no_food > 0.0f;
		if(ftrying) {
			tried_no_food += 0.1f;
			if(tried_no_food > tried_no_food_max) {
				tried_no_food = -1.0f;
			}
		}

		float sw = (float) al_get_bitmap_width(gm_global_state.empty);
		float sh = (float) al_get_bitmap_height(gm_global_state.empty);
		float bar_x = 16.0f;
		float bar_y = gm_global_state.height - (sh * gm_global_state.camera.zoom) - 16.0f;
		float offx = ftrying ? gm_sign_random() * 4.0f * (tried_no_food_max - tried_no_food) : 0.0f;
		float offy = ftrying ? gm_sign_random() * 4.0f * (tried_no_food_max - tried_no_food) : 0.0f;
		ALLEGRO_COLOR tting = ftrying ? al_map_rgb_f(1.0f, 0.0f, 0.0f) : al_map_rgb_f(1.0f, 1.0f, 1.0f);
		al_draw_tinted_scaled_bitmap(
				gm_global_state.empty,
				tting,
				0, 0, sw, sh,
				bar_x + (gm_random() * gm_global_state.camera.jitter) + offx,
				bar_y + (gm_random() * gm_global_state.camera.jitter) + offy,
				sw * gm_global_state.camera.zoom, sh * gm_global_state.camera.zoom, 0);

		float filled_inset = 23.0f;
		float filled_tail = 3.0f;
		float fillw = sw - filled_inset - filled_tail;
		float fullness = gm_global_state.fullness / gm_global_state.max_fullness;
		float fill_x_start = bar_x + (filled_inset * gm_global_state.camera.zoom) + (gm_random() * gm_global_state.camera.jitter) + offx;
		float fill_y_start = bar_y + (gm_random() * gm_global_state.camera.jitter) + offy;
		float fill_x_w = fillw * fullness;
		al_draw_tinted_scaled_rotated_bitmap_region(
				gm_global_state.full, filled_inset, 0, fill_x_w, sh,
				tting, 0.0f, 0.0f, fill_x_start, fill_y_start,
				gm_global_state.camera.zoom, gm_global_state.camera.zoom, 0.0f, 0);

		al_draw_tinted_scaled_bitmap(
				gm_global_state.marker, tting, 0, 0, 16, 16,
				fill_x_start + ((fillw) * fullness * gm_global_state.camera.zoom) - (8 * gm_global_state.camera.zoom),
				fill_y_start - (6 * gm_global_state.camera.zoom), gm_global_state.camera.zoom * 16, gm_global_state.camera.zoom * 16, 0);

		float wdemand = winfo->cost / gm_global_state.max_fullness;
		al_draw_tinted_scaled_bitmap(
				gm_global_state.pwmarker, tting, 0, 0, 16, 20,
				fill_x_start + ((fillw) * wdemand * gm_global_state.camera.zoom) - (8 * gm_global_state.camera.zoom),
				fill_y_start + (2 * gm_global_state.camera.zoom), gm_global_state.camera.zoom * 16, gm_global_state.camera.zoom * 20, 0);

		al_draw_tinted_scaled_rotated_bitmap_region(
				gm_global_state.object_tileset.atlas, sx, sy, wsw, wsh,
				al_map_rgb_f(1.0f, 1.0f, 1.0f),
				8, 8,
				bar_x + (12 * gm_global_state.camera.zoom), bar_y + (12 * gm_global_state.camera.zoom),
				gm_global_state.camera.zoom, gm_global_state.camera.zoom, gm_global_state.aim + (3.14f / 4.0f), 0);

		gm_global_state.camera.color_pulse += (fullness * fullness) / 8.0f;
		if(fullness > 0.85) {
			gm_global_state.camera.jitter += 0.5f;
		}

		int money_a = gm_global_state.money / 10;
		int money_b = gm_global_state.money % 10;

		int id_a = 181 + money_a;
		int id_b = 181 + money_b;

		gm_draw_money_tile(id_a, gm_global_state.width - (18 * 3 * gm_global_state.camera.zoom), 0.0f);
		gm_draw_money_tile(id_b, gm_global_state.width - (18 * 2 * gm_global_state.camera.zoom), 0.0f);

		al_draw_tinted_scaled_rotated_bitmap_region(
				gm_global_state.object_tileset.atlas,
				6 * 16,
				4 * 16,
				16, 16,
				al_map_rgb_f(1.0f, 1.0f, 1.0f),
				8, 8,
				gm_global_state.width - (20 * gm_global_state.camera.zoom),
				gm_global_state.height - (20 * gm_global_state.camera.zoom),
				gm_global_state.camera.zoom, gm_global_state.camera.zoom, 0, 0);

		int id_c = 181 + gm_global_state.keys;

		float cofy = 18.0f;
		gm_draw_money_tile(id_c, gm_global_state.width - (18 * 2 * gm_global_state.camera.zoom), cofy * gm_global_state.camera.zoom);

		al_draw_tinted_scaled_rotated_bitmap_region(
				gm_global_state.object_tileset.atlas,
				3 * 16,
				5 * 16,
				16, 16,
				al_map_rgb_f(1.0f, 1.0f, 1.0f),
				8, 8,
				gm_global_state.width - (20 * gm_global_state.camera.zoom),
				gm_global_state.height - (20 * gm_global_state.camera.zoom) - (cofy * gm_global_state.camera.zoom),
				gm_global_state.camera.zoom, gm_global_state.camera.zoom, 0, 0);

		gm_do_oven();
	}

	struct nk_rect area = nk_rect(50, 50, 320, 520);
	enum nk_panel_flags flags =
			NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_TITLE;

	if(false && nk_begin(ui->context, "game", area, flags)) {
		nk_layout_row_static(ui->context, 30, 180, 1);

		nk_property_int(ui->context, "Money", 0, &gm_global_state.money, 50, 1, 1);
		nk_property_int(ui->context, "Keys", 0, &gm_global_state.keys, 50, 1, 1);

		nk_property_float(ui->context, "X", 0, &gm_global_state.oven.bx, 1600, 1, 1);
		nk_property_float(ui->context, "Y", 0, &gm_global_state.oven.by, 1600, 1, 1);
		nk_property_float(ui->context, "Health", 0, &gm_global_state.oven.health, gm_global_state.oven.max_health, 1, 1);

		if(nk_tree_push(ui->context, NK_TREE_TAB, "Light & Camera", NK_MINIMIZED)) {
			nk_property_float(
					ui->context, "linear",
					-100.0f, &gm_global_state.light.linear, 100.0f, 0.1f, 0.1f);

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

			nk_tree_pop(ui->context);
		}

		for(size_t i = 0; i < GM_WEAPON_COUNT; ++i) {
			auto weapon = &gm_global_weapon_info[i];
			if(nk_tree_push(ui->context, NK_TREE_TAB, weapon->name, NK_MINIMIZED)) {
				nk_property_float(ui->context, "radius", 0.0f, &weapon->radius, 50.0f, 0.5f, 0.5f);
				nk_property_float(ui->context, "damage", 0.0f, &weapon->damage, 50.0f, 0.5f, 0.5f);
				nk_property_float(ui->context, "knockback", 0.0f, &weapon->knockback, 50.0f, 0.5f, 0.5f);
				nk_tree_pop(ui->context);
			}
		}

		for(size_t i = 0; i < GM_ENEMY_COUNT; ++i) {
			auto enemy = &gm_global_enemy_info[i];
			if(nk_tree_push(ui->context, NK_TREE_TAB, enemy->name, NK_MINIMIZED)) {
				nk_property_float(ui->context, "health", 0.0f, &enemy->health, 50.0f, 0.5f, 0.5f);
				nk_property_float(ui->context, "dampening", 0.0f, &enemy->dampening, 1.0f, 0.05f, 0.05f);
				nk_property_float(ui->context, "width_mul", 0.0f, &enemy->width_mul, 50.0f, 0.5f, 0.5f);
				nk_property_float(ui->context, "follow_force", 0.0f, &enemy->follow_force, 5.0f, 0.01f, 0.01f);
				nk_property_float(ui->context, "force_cap", 0.0f, &enemy->force_cap, 50.0f, 0.5f, 0.5f);
				nk_property_float(ui->context, "follow_distance", 0.0f, &enemy->follow_distance, 5000.0f, 0.5f, 0.5f);
				nk_tree_pop(ui->context);
			}
		}
		nk_end(ui->context);
	}

	return PDN_RESULT_OK;
}
