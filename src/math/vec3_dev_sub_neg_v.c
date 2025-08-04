#include "vec3.h"

t_vec3	vec3_negate_v(const t_vec3 *const input)
{
	t_vec3	result;

	vec3_copy(&result, input);
	vec3_negate(&result);
	return (result);
}

t_vec3	vec3_add_v(const t_vec3 *const input, const t_vec3 *const addent)
{
	t_vec3	result;
	
	vec3_copy(&result, input);
	result.z += addent->z;
	result.y += addent->y;
	result.z += addent->z;
	return (result);
}

t_vec3	vec3_devide_by_const_v(const t_vec3 *const input, const FLOAT divisor)
{
	t_vec3	divident;

	vec3_copy(&divident, input);
	divident.x /= divisor;
	divident.y /= divisor;
	divident.z /= divisor;
	return (divident);
}
