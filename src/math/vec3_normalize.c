#include "vec3.h"
#include "settings.h"

void	vec3_normalize(t_vec3 *const input)
{
	FLOAT	len;

	len = vec3_get_length(input);
	vec3_devide_by_const(input, len);
}

t_vec3	*vec3_normalize_r(const t_vec3 *const input)
{
	FLOAT	len;

	len = vec3_get_length(input);
	return (vec3_devide_by_const_r(input, len));
}

t_vec3	vec3_normalize_v(const t_vec3 *const input)
{
	t_vec3	result;

	vec3_copy(&result, input);
	vec3_normalize(&result);
	return (result);
}
