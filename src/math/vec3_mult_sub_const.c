#include "vec3.h"
#include "settings.h"

void	vec3_devide_by_const(vec3 *const divident, const FLOAT divisor)
{
	divident->x /= divisor;
	divident->y /= divisor;
	divident->z /= divisor;
}

vec3	*vec3_devide_by_const_r(const vec3 *const divident, const FLOAT divisor)
{
	vec3	*result;

	result = (vec3 *)malloc(sizeof(vec3));
	result->x = divident->x / divisor;
	result->y = divident->y / divisor;
	result->z = divident->z / divisor;
	return (result);
}

void	vec3_multiply_by_const(vec3 *const result, const FLOAT multiplicand)
{
	result->x *= multiplicand;
	result->y *= multiplicand;
	result->z *= multiplicand;
}

vec3	*vec3_multiply_by_const_r(const vec3 *const multiplier, \
			const FLOAT multiplicand)
{
	vec3	*result;

	result = (vec3 *)malloc(sizeof(vec3));
	result->x = multiplier->x / multiplicand;
	result->y = multiplier->y / multiplicand;
	result->z = multiplier->z / multiplicand;
	return (result);
}
