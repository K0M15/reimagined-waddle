#include <stdlib.h>
#include "vec3.h"

void	vec3_copy(t_vec3 *const result, const t_vec3 *const source)
{
	result->x = source->x;
	result->y = source->y;
	result->z = source->z;
}

t_vec3	*vec3_dup(const t_vec3 *const source)
{
	t_vec3	*result;

	result = (t_vec3 *)malloc(sizeof(t_vec3));
	if (!result)
		return (0);
	result->x = source->x;
	result->y = source->y;
	result->z = source->z;
	return (result);
}
