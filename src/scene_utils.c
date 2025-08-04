#include "minirt.h"
#include "elements.h"
#include "settings.h"

t_scene *get_scene(void)
{
	static t_scene scene;
	return (&scene);
}

static void	init_scene_settings(void)
{
	t_point		*temp;
	t_settings	*settings;

	settings = &(get_scene()->settings);
	settings->viewport_height = (FLOAT)2.0;
	settings->viewport_width = \
	settings->viewport_width * ((double)IMAGE_WIDTH / IMAGE_HEIGHT);
	vec3_copy(&settings->pixel_delta_h, (t_point[]){{.x = 0, .y = settings->viewport_height / IMAGE_HEIGHT, .z = 0}});
	vec3_copy(&settings->pixel_delta_w, (t_point[]){{.x = settings->viewport_width / IMAGE_WIDTH, .y = 0, .z = 0}});
	temp = &(settings->viewport_left);
	//TODO: The value will change based on camera position
	vec3_copy(temp, (t_point[]){{.x = 0, .y = 0, .z = 0}});
	vec3_subtract(temp, (t_point[]){{.x = get_scene()->settings.viewport_width, \
		.y = get_scene()->settings.viewport_height, .z = FOCAL_LENGTH}});
	temp = &(get_scene()->settings.first_pixel);
	vec3_copy(temp, &(get_scene()->settings.viewport_left));
	vec3_add(temp, (t_point[]){{.x = settings->pixel_delta_w.x * 0.5, \
		.y = settings->pixel_delta_h.y * 0.5, .z = 0}});
}

void	init_scene(void)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < IMAGE_HEIGHT)
	{
		while (x < IMAGE_WIDTH)
		{
			get_scene()->pixels[y][x].r = 0;
			get_scene()->pixels[y][x].g = 0;
			get_scene()->pixels[y][x].b = 0;
			x++;
		}
		x = 0;
		y++;
	} 
	init_scene_settings();
	get_scene()->ambient_light = 0;
	get_scene()->camera = 0;
	get_scene()->light = 0;
	get_scene()->sphere = 0;
	get_scene()->plane = 0;
	get_scene()->cylinder = 0;
}
