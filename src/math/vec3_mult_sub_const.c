#include <stdlib.h>
#include "vec3.h"
#include "settings.h"

void	vec3_devide_by_const(t_vec3 *const divident, const FLOAT divisor)
{
	divident->x /= divisor;
	divident->y /= divisor;
	divident->z /= divisor;
}

t_vec3	*vec3_devide_by_const_r(const t_vec3 *const divident, const FLOAT divisor)
{
	t_vec3	*result;

	result = (t_vec3 *)malloc(sizeof(t_vec3));
	if (!result)
		return (0);
	result->x = divident->x / divisor;
	result->y = divident->y / divisor;
	result->z = divident->z / divisor;
	return (result);
}

void	vec3_multiply_by_const(t_vec3 *const result, const FLOAT multiplicand)
{
	result->x *= multiplicand;
	result->y *= multiplicand;
	result->z *= multiplicand;
}

t_vec3	*vec3_multiply_by_const_r(const t_vec3 *const multiplier, \
			const FLOAT multiplicand)
{
	t_vec3	*result;

	result = (t_vec3 *)malloc(sizeof(t_vec3));
	if (!result)
		return (0);
	result->x = multiplier->x / multiplicand;
	result->y = multiplier->y / multiplicand;
	result->z = multiplier->z / multiplicand;
	return (result);
}

t_vec3	vec3_multiply_by_const_v(const t_vec3 *const input, const FLOAT multiplicand)
{
	t_vec3	result;

	vec3_copy(&result, input);
	result.x *= multiplicand;
	result.y *= multiplicand;
	result.z *= multiplicand;
	return (result);
}
