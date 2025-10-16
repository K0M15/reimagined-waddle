/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftvec3_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:10:16 by afelger           #+#    #+#             */
/*   Updated: 2025/10/16 13:11:04 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftvec3.h"

t_vec3	ftvec3_rclamped(double min, double max)
{
	double	scale;

	scale = max - min;
	return ((t_vec3){
		clamp((rand_double() - 0.5) * scale, min, max),
		clamp((rand_double() - 0.5) * scale, min, max),
		clamp((rand_double() - 0.5) * scale, min, max)
	});
}

t_vec3	ftvec3_runit(void)
{
	t_vec3	p;
	double	lensq;

	p = ftvec3_rclamped(-1, 1);
	lensq = ftvec3_length(p) * ftvec3_length(p);
	while (1e160 < lensq && lensq <= 1)
	{
		p = ftvec3_rclamped(-1, 1);
		lensq = ftvec3_length(p) * ftvec3_length(p);
	}
	return (ftvec3_divide(p, ftvec3(sqrt(lensq))));
}

t_vec3	ftvec3_ronhemi(t_vec3 normal)
{
	t_vec3	on_hemi;

	on_hemi = ftvec3_runit();
	if (ftvec3_dot(on_hemi, normal) > 0.0)
		return (on_hemi);
	return (ftvec3_multiply(on_hemi, ftvec3(-1)));
}

t_vec3	ftvec3_plus(t_vec3 op1, t_vec3 op2)
{
	t_vec3	result;

	result.x = op1.x + op2.x;
	result.y = op1.y + op2.y;
	result.z = op1.z + op2.z;
	return (result);
}
