#ifndef	VEC3_H
# define VEC3_H
#include <settings.h>

typedef struct s_vec3 {
	FLOAT x;
	FLOAT y;
	FLOAT z;
} vec3;

void	vec3_negate(vec3 *const);
vec3	*vec3_negate_r(const vec3 *const);

void	vec3_add(vec3 *const result, const vec3 *const addent);
vec3	*vec3_add_r(const vec3 *const addent1, const vec3 *const addent2);

void	vec3_subtract(vec3 *const, const vec3 *const);
vec3	*vec3_subtract_r(const vec3 *const, const vec3 *const);

void	vec3_devide_by_const(vec3 *const, const FLOAT);
vec3	*vec3_devide_by_const_r(const vec3 *const, const FLOAT);

void	vec3_multiply_by_const(vec3 *const, const FLOAT);
vec3	*vec3_multiply_by_const_r(const vec3 *const, const FLOAT);

FLOAT	vec3_get_length(const vec3 *const);
FLOAT	vec3_get_length_squared(const vec3 *const);

void	vec3_multiply_by(vec3 *const, const vec3 *const);
vec3	*vec3_multiply_by_r(const vec3 *const, const vec3 *const);

void	vec3_unit_vec(vec3 *const);
vec3	*vec3_unit_vec_r(const vec3 *const);

FLOAT	vec3_dot_product(const vec3 *const, const vec3 *const);

void	vec3_cross_procuct(vec3 *const, const vec3 *const);
vec3	*vec3_cross_procuct_r(const vec3 *const, const vec3 *const);

//For debuging
void	vec3_print(const vec3 *const);

#endif

