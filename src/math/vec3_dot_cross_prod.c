#include <stdlib.h>
#include "vec3.h"
#include "settings.h"

FLOAT	vec3_dot_product(const vec3 *const a, const vec3 *const b)
{
	FLOAT	result;

	result = 0;
	result += a->x * b->x;
	result += a->y * b->y;
	result += a->z * b->z;
	return (result);
}

void	vec3_cross_procuct(vec3 *const result, const vec3 *const b)
{
	vec3	temp;

	temp.x = result->x;
	temp.y = result->y;
	temp.z = result->z;
	result->x = temp.y * b->z - temp.z * b->y;
	result->y = temp.x * b->z - temp.z * b->x;
	result->z = temp.x * b->y - temp.y * b->x;
}

vec3	*vec3_cross_procuct_r(const vec3 *const a, const vec3 *const b)
{
	vec3	*result;

	result = (vec3 *)malloc(sizeof(vec3));
	if (!result)
		return (0);
	result->x = a->y * b->z - a->z * b->y;
	result->y = a->x * b->z - a->z * b->x;
	result->z = a->x * b->y - a->y * b->x;
	return (result);
}
