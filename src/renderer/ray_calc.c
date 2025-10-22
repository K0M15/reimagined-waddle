#include "ray.h"
#include "vec3.h"
#include "settings.h"

t_point	get_ray_at(t_ray *ray, FLOAT at)
{
	t_point	ret;

	vec3_copy(&ret, &ray->normal);
	vec3_multiply_by_const(&ret, at);
	vec3_add(&ret, &ray->origin);
	return (ret);
} 
