#include "minirt.h"
#include "elememts.h"

t_scene *get_scene(void)
{
	static const t_scene scene;
	return (&scene);
}

void	init_scene(void)
{
	get_scene()->ambient_light = 0;
	get_scene()->camera = 0;
	get_scene()->light = 0;
	get_scene()->sphere = 0;
	get_scene()->plane = 0;
	get_scene()->cylinder = 0;
}
