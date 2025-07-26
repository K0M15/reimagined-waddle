#include <math.h>
#include "vec3.h"
#include "settings.h"

FLOAT	vec3_get_length(const vec3 *const input)
{
	return (sqrt(vec3_get_length_squared(input)));
}

FLOAT	vec3_get_length_squared(const vec3 *const input)
{
	return (input->x * input->x + \
			input->y * input->y + \
			input->z * input->z);
}

//TODO: Discuss if this op is needed
void	vec3_multiply_by(vec3 *const input1, const vec3 *const input2)
{
	(void) input1;
	(void) input2;
}

//TODO: Discuss if this op is needed
vec3	*vec3_multiply_by_r(const vec3 *const input1, const vec3 *const input2)
{
	(void) input1;
	(void) input2;
	return (0);
}
