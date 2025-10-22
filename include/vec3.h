#ifndef	VEC3_H
# define VEC3_H
#include <settings.h>

// typedef struct s_vec3 {
// 	FLOAT x;
// 	FLOAT y;
// 	FLOAT z;
// } t_vec3;

// void	vec3_copy(t_vec3 *const result, const t_vec3 *const source);
// t_vec3	*vec3_dup(const t_vec3 *const);

// void	vec3_negate(t_vec3 *const);
// t_vec3	*vec3_negate_r(const t_vec3 *const);
// t_vec3	vec3_negate_v(const t_vec3 *const);

// void	vec3_add(t_vec3 *const result, const t_vec3 *const addent);
// t_vec3	*vec3_add_r(const t_vec3 *const addent1, const t_vec3 *const addent2);
// t_vec3	vec3_add_v(const t_vec3 *const addent1, const t_vec3 *const addent2);

// void	vec3_subtract(t_vec3 *const, const t_vec3 *const);
// t_vec3	*vec3_subtract_r(const t_vec3 *const, const t_vec3 *const);
// t_vec3	vec3_subtract_v(const t_vec3 *const, const t_vec3 *const);

// void	vec3_devide_by_const(t_vec3 *const, const FLOAT);
// t_vec3	*vec3_devide_by_const_r(const t_vec3 *const, const FLOAT);
// t_vec3	vec3_devide_by_const_v(const t_vec3 *const, const FLOAT);

// void	vec3_multiply_by_const(t_vec3 *const, const FLOAT);
// t_vec3	*vec3_multiply_by_const_r(const t_vec3 *const, const FLOAT);
// t_vec3	vec3_multiply_by_const_v(const t_vec3 *const, const FLOAT);

// FLOAT	vec3_get_length(const t_vec3 *const);
// FLOAT	vec3_get_length_squared(const t_vec3 *const);

// void	vec3_unit_vec(t_vec3 *const);
// t_vec3	*vec3_unit_vec_r(const t_vec3 *const);
// t_vec3	vec3_unit_vec_v(const t_vec3 *const);

// FLOAT	vec3_dot_product(const t_vec3 *const, const t_vec3 *const);

// void	vec3_cross_procuct(t_vec3 *const, const t_vec3 *const);
// t_vec3	*vec3_cross_procuct_r(const t_vec3 *const, const t_vec3 *const);
// t_vec3	vec3_cross_procuct_v(const t_vec3 *const, const t_vec3 *const);

// void	vec3_normalize(t_vec3 *const input);
// t_vec3	*vec3_normalize_r(const t_vec3 *const input);
// t_vec3	vec3_normalize_v(const t_vec3 *const input);

//For debuging
void	vec3_print(const t_vec3 *const);

#endif
