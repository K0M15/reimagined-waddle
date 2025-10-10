#include "vec3.h"

void	vec3_negate(t_vec3 *const result)
{
	result->x = -result->x;
	result->y = -result->y;
	result->z = -result->z;
}

t_vec3	*vec3_negate_r(const t_vec3 *const input)
{
	t_vec3	*result;

	result = vec3_dup(input);
	if (!result)
		return (0);
	vec3_negate(result);
	return (result);
}

void	vec3_unit_vec(t_vec3 *const result)
{
	vec3_devide_by_const(result, vec3_get_length(result));
}

t_vec3	*vec3_unit_vec_r(const t_vec3 *const input)
{
	t_vec3	*result;

	result = vec3_devide_by_const_r(input, vec3_get_length(input));
	return (result);
}

t_vec3	vec3_unit_vec_v(const t_vec3 *const input)
{
	t_vec3	result;

	vec3_copy(&result, input);
	vec3_devide_by_const(&result, vec3_get_length(&result));
	return (result);
}
