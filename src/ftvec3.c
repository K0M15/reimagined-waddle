/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftvec3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:51:41 by afelger           #+#    #+#             */
/*   Updated: 2025/10/16 13:10:32 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftvec3.h"

t_vec3	ftvec3_reflect(t_vec3 vec, t_vec3 norm)
{
	t_vec3	dot;

	dot = ftvec3(ftvec3_dot(vec, norm));
	return (ftvec3_minus(vec,
			ftvec3_multiply(ftvec3(2), ftvec3_multiply(dot, norm))));
}

bool	ftvec3_near_zero(t_vec3 vec)
{
	return ((fabs(vec.x) < DOUBLE_NEAR_ZERO)
		&& (fabs(vec.y) < DOUBLE_NEAR_ZERO)
		&& (fabs(vec.z) < DOUBLE_NEAR_ZERO));
}

t_vec3	ftvec3_lin_gamma(t_vec3 vec)
{
	return ((t_vec3){
		linear_to_gamma(vec.x),
		linear_to_gamma(vec.y),
		linear_to_gamma(vec.z)});
}

double	clamp(double f, double min, double max)
{
	if (f < min)
		return (min);
	if (f > max)
		return (max);
	return (f);
}

t_vec3	ftvec3_random(void)
{
	return ((t_vec3){rand_double(), rand_double(), rand_double()});
}
