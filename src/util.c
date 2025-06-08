// Position is pre-scaled.
float gm_light_attenuate(struct gm_light* light, struct gm_camera* camera, float x, float y) {
	float light_x = (light->x * camera->zoom) - camera->x;
	float light_y = (light->y * camera->zoom) - camera->y;

	float dxl = fabsf(x - light_x);
	float dyl = fabsf(y - light_y);
	float linear = (light->linear * camera->zoom) / (dxl + dyl);
	float quadratic = (light->quadratic * camera->zoom) / sqrtf(dxl + dxl + dyl + dyl);

	float dl = linear + quadratic;
	return roundf(dl * light->clamp) / light->clamp;
}

float gm_random(void) {
	return (float) rand() / (float) RAND_MAX;
}

float gm_sign_random(void) {
	return ((float) rand() / (float) RAND_MAX) - 0.5f;
}

ALLEGRO_COLOR gm_color_multiply(ALLEGRO_COLOR color, float value) {
	return al_map_rgb_f(color.r * value, color.g * value, color.b * value);
}

ALLEGRO_COLOR gm_color_sub_color(ALLEGRO_COLOR color, ALLEGRO_COLOR other) {

	return al_map_rgb_f(
			GM_MAX(color.r - other.r, 0), GM_MAX(color.g - other.g, 0), GM_MAX(color.b - other.b, 0));
}

ALLEGRO_COLOR gm_color_add_color(ALLEGRO_COLOR color, ALLEGRO_COLOR other) {

	return al_map_rgb_f(
			color.r + other.r, color.g + other.g, color.b + other.b);
}

ALLEGRO_COLOR gm_color_random() {
	return al_map_rgb_f(gm_random(), gm_random(), gm_random());
}

ALLEGRO_COLOR gm_color_multiply_color(ALLEGRO_COLOR color, ALLEGRO_COLOR other) {

	return al_map_rgb_f(
			color.r * other.r, color.g * other.g, color.b * other.b);
}
