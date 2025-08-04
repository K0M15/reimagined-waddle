#include "minirt.h"
#include "elements.h"
#include "settings.h"

t_scene *get_scene(void)
{
	static t_scene scene;
	return (&scene);
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
	get_scene()->ambient_light = 0;
	get_scene()->camera = 0;
	get_scene()->light = 0;
	get_scene()->sphere = 0;
	get_scene()->plane = 0;
	get_scene()->cylinder = 0;
}
