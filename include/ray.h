#include "settings.h"
#include "elements.h"

typedef struct s_ray {
	t_point		origin;
	t_normal	normal;
}t_ray;

t_point	get_ray_at(t_ray *ray, FLOAT at);
