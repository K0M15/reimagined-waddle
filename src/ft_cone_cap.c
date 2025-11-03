/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cone_cap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:05:30 by afelger           #+#    #+#             */
/*   Updated: 2025/11/03 14:09:38 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hitable.h"
#include "ftvec3.h"

static void	fillvars(t_vec3 *cap, const t_props *c, t_vec3 axis)
{
	cap[0] = c->position;
	cap[1] = ftvec3_multiply(axis, ftvec3(-1.0f));
}

static int	check_hit(t_vec3 p, const t_props *c, t_vec3 ci, t_vec3 axis)
{
	return (ftvec3_dot(ftvec3_minus(ftvec3_minus(p, ci),
				ftvec3_multiply(axis, ftvec3(ftvec3_dot(ftvec3_minus(p, ci),
							axis)))),
			ftvec3_minus(ftvec3_minus(p, ci),
				ftvec3_multiply(axis, ftvec3(ftvec3_dot(ftvec3_minus(
								p, ci), axis)))))
		<= c->radius * c->radius + 1e-6f);
}

t_hitrec	find_conecap_hit(t_vec3 axis, const t_props *c,
	t_ray ray, struct s_lpair limit)
{
	t_vec3		cap[3];
	t_hitrec	result;
	double		tcap;

	fillvars(cap, c, axis);
	result = (t_hitrec){ftvec3(0), ftvec3(0), NULL, INFINITY, 0, {.0f, .0f}};
	if (fabs(ftvec3_dot(axis, ray.direction)) < FLOAT_NEAR_ZERO)
		return (result);
	tcap = ftvec3_dot(axis, ftvec3_minus(cap[0], ray.origin))
		/ ftvec3_dot(axis, ray.direction);
	if (!(tcap > limit.min && tcap < limit.max))
		return (result);
	cap[2] = ftray_at(ray, tcap);
	if (check_hit(cap[2], c, cap[0], axis))
	{
		result = (t_hitrec){cap[2], cap[1],
			NULL, tcap, false, {.0f, .0f}};
		result.uv = uv_plane((t_props){
				ftvec3(0), cap[0], cap[1], 0, 0, 0, 0,}, result.hit);
	}
	return (result);
}

void	ft_cone_basis(t_vec3 normal, t_vec3 axis, t_vec3 basis[3])
{
	basis[2] = ftvec3_unit(normal);
	basis[1] = ftvec3_unit(axis);
	basis[0] = ftvec3_unit(ftvec3_cross(basis[1], basis[2]));
}

t_vec3	cone_norm(t_vec3 p, const t_props *c, float proj, float k)
{
	return (ftvec3_unit(
			ftvec3_minus(
				ftvec3_minus(
					ftvec3_minus(p, c->position),
					ftvec3_multiply(c->rotation, ftvec3(proj))),
				ftvec3_multiply(c->rotation, ftvec3(k * (c->radius + k * proj)
					)))));
}
