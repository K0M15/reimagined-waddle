#include <stdlib.h>
#include "vec3.h"

void	vec3_copy(vec3 *const result, const vec3 *const source)
{
	result->x = source->x;
	result->y = source->y;
	result->z = source->z;
}

vec3	*vec3_dup(const vec3 *const source)
{
	vec3	*result;

	result = (vec3 *)malloc(sizeof(vec3));
	if (!result)
		return (0);
	result->x = source->x;
	result->y = source->y;
	result->z = source->z;
	return (result);
}
