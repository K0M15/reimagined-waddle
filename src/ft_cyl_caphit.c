/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cyl_caphit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:21:59 by afelger           #+#    #+#             */
/*   Updated: 2025/11/03 19:45:53 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hitable.h"
#include "ftvec3.h"

void	ft_cyl_basis(t_vec3 normal, t_vec3 axis, t_vec3 basis[3])
{
	basis[2] = ftvec3_unit(normal);
	basis[1] = ftvec3_unit(axis);
	basis[0] = ftvec3_unit(ftvec3_cross(basis[1], basis[2]));
}

static int	fillvars(t_vec3 *cap, t_props *c, t_vec3 axis)
{
	cap[0] = c->position;
	cap[1] = ftvec3_plus(c->position, ftvec3_multiply(axis, ftvec3(c->height)));
	cap[2] = ftvec3_multiply(axis, ftvec3(-1.0f));
	cap[3] = axis;
	return (-1);
}

static int	check_hit(t_vec3 p, t_props *c, t_vec3 ci, t_vec3 axis)
{
	return (ftvec3_dot(ftvec3_minus(ftvec3_minus(p, ci),
				ftvec3_multiply(axis, ftvec3(ftvec3_dot(ftvec3_minus(p, ci),
							axis)))),
			ftvec3_minus(ftvec3_minus(p, ci),
				ftvec3_multiply(axis, ftvec3(ftvec3_dot(ftvec3_minus(
								p, ci), axis)))))
		<= c->radius * c->radius + 1e-6f);
}

// TOCHECK: Somehow i am not using the inverse of the surface normal of the caps
t_hitrec	find_cap_hit(t_vec3 axis, t_props *c,
	t_ray ray, struct s_lpair limit)
{
	t_vec3		cap[5];
	t_hitrec	result;
	double		tcap;
	int			ci;

	ci = fillvars(cap, c, axis);
	result = (t_hitrec){ftvec3(0), ftvec3(0), NULL, INFINITY, 0, {.0f, .0f}};
	while (++ci < 2)
	{
		if (fabs(ftvec3_dot(axis, ray.direction)) < FLOAT_NEAR_ZERO)
			continue ;
		tcap = ftvec3_dot(axis, ftvec3_minus(cap[ci], ray.origin))
			/ ftvec3_dot(axis, ray.direction);
		if (!(tcap > limit.min && tcap < limit.max))
			continue ;
		cap[4] = ftray_at(ray, tcap);
		if (check_hit(cap[4], c, cap[ci], axis))
			if (tcap < result.t)
			{
				result = (t_hitrec){cap[4], cap[ci + 2],
					NULL, tcap, false, {.0f, .0f}};
				result.uv = uv_plane((t_props){ftvec3(0), cap[ci + 2],
						cap[4], 0, 0, 0, 0}, result.hit);
			}
	}
	return (result);
}
