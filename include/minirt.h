#ifndef	MINIRT_H
# define MINIRT_H
#include "elements.h"
#include "ft_ll.h"

//typedef struct s_scene {
//	t_ambient_light	*ambient_light;
//	t_camera 	*camera;
//	t_light		*light;
//	t_sphere	*sphere;
//	t_plane		*plane;
//	t_cylinder	*cylinder;
//} t_scene;

//Because C compiles in row major order the order is pixel[y][x]
//Pixels should be stored with values from 0 - 255
typedef struct s_scene {
	t_rgb	pixels[IMAGE_HEIGHT][IMAGE_WIDTH];
	t_node	*ambient_light;
	t_node 	*camera;
	t_node	*light;
	t_node	*sphere;
	t_node	*plane;
	t_node	*cylinder;
} t_scene;

t_scene *get_scene(void);
void	init_scene(void);
void	render(const char * input);

#endif
