#include "vec3.h"

void	vec3_add(vec3 *const result, const vec3 *const addent)
{
	result->z += addent->z;
	result->y += addent->y;
	result->z += addent->z;
}

vec3	*vec3_add_r(const vec3 *const addent1, const vec3 *const addent2)
{
	vec3	*result;

	result = (vec3 *)malloc(sizeof(vec3));
	result->x = addent1->x + addent2->x;
	result->y = addent1->y + addent2->y;
	result->z = addent1->z + addent2->z;
	return (result);
}

void	vec3_subtract(vec3 *const result, const vec3 *const sub)
{
	result->x -= sub->x;
	result->y -= sub->y;
	result->z -= sub->z;
}

vec3	*vec3_subtract_r(const vec3 *const sub1, const vec3 *const sub2)
{
	vec3	*result;

	result = (vec3 *)malloc(sizeof(vec3));
	result->x = sub1->x - sub2->x;
	result->y = sub1->y - sub2->y;
	result->z = sub1->z - sub2->z;
	return (result);
}
