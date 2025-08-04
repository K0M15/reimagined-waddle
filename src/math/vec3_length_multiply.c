#include <math.h>
#include "vec3.h"
#include "settings.h"

FLOAT	vec3_get_length(const t_vec3 *const input)
{
	return (sqrt(vec3_get_length_squared(input)));
}

FLOAT	vec3_get_length_squared(const t_vec3 *const input)
{
	return (input->x * input->x + \
			input->y * input->y + \
			input->z * input->z);
}
