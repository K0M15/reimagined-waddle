#ifndef	MINIRT_H
# define MINIRT_H
#include "elements.h"

typedef struct s_scene {
	t_ambient_light	*ambient_light;
	t_camera 	*camera;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
} t_scene;

t_scene *get_scene(void);
void	init_scene(void);

#endif
