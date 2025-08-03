#include <stdlib.h>
#include "vec3.h"

void	vec3_add(t_vec3 *const result, const t_vec3 *const addent)
{
	result->z += addent->z;
	result->y += addent->y;
	result->z += addent->z;
}

t_vec3	*vec3_add_r(const t_vec3 *const addent1, const t_vec3 *const addent2)
{
	t_vec3	*result;

	result = (t_vec3 *)malloc(sizeof(t_vec3));
	if (!result)
		return (0);
	result->x = addent1->x + addent2->x;
	result->y = addent1->y + addent2->y;
	result->z = addent1->z + addent2->z;
	return (result);
}

void	vec3_subtract(t_vec3 *const result, const t_vec3 *const sub)
{
	result->x -= sub->x;
	result->y -= sub->y;
	result->z -= sub->z;
}

t_vec3	*vec3_subtract_r(const t_vec3 *const sub1, const t_vec3 *const sub2)
{
	t_vec3	*result;

	result = (t_vec3 *)malloc(sizeof(t_vec3));
	if (!result)
		return (0);
	result->x = sub1->x - sub2->x;
	result->y = sub1->y - sub2->y;
	result->z = sub1->z - sub2->z;
	return (result);
}
