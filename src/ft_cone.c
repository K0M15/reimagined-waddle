/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:31:26 by afelger           #+#    #+#             */
/*   Updated: 2025/11/04 15:03:58 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hitable.h"
#include "ftvec3.h"

static t_vec3	fillabc(t_vec3 axis, const t_props *c, t_vec3 ro_base,
	t_ray ray)
{
	t_vec3	abc;
	t_vec3	q0;
	t_vec3	q1;
	float	k;

	k = 0.0f;
	if (c->height != 0.0f)
		k = (-c->radius / c->height);
	q0 = ftvec3_minus(ro_base, ftvec3_multiply(axis, ftvec3(
					ftvec3_dot(ro_base, axis))));
	q1 = ftvec3_minus(ray.direction, ftvec3_multiply(axis,
				ftvec3(ftvec3_dot(ray.direction, axis))));
	abc.x = ftvec3_dot(q1, q1) - (k * k) * (ftvec3_dot(ray.direction, axis)
			* ftvec3_dot(ray.direction, axis));
	abc.y = 2.0f * (ftvec3_dot(q0, q1) - (c->radius + k * ftvec3_dot(ro_base,
					axis)) * (k * ftvec3_dot(ray.direction, axis)));
	abc.z = ftvec3_dot(q0, q0) - (c->radius + k * ftvec3_dot(ro_base, axis))
		* (c->radius + k * ftvec3_dot(ro_base, axis));
	return (abc);
}

static t_hitrec	find_root_hit(float drr[3], t_ray ray,
	struct s_lpair limit, const t_props *c)
{
	t_vec3		p;
	t_hitrec	hit;
	float		proj_k[2];
	int			ri;

	ri = 0;
	hit = (t_hitrec){ftvec3(0), ftvec3(0), NULL,
		INFINITY, 0, (t_uv){0.0f, 0.0f}};
	proj_k[1] = 0.0f;
	if (c->height != 0.0f)
		proj_k[1] = -c->radius / c->height;
	while (++ri < 3)
	{
		if (!(drr[ri] > limit.min && drr[ri] < limit.max))
			continue ;
		p = ftray_at(ray, drr[ri]);
		proj_k[0] = ftvec3_dot(ftvec3_minus(p, c->position),
				ftvec3_unit(c->rotation));
		if (proj_k[0] >= -FLOAT_NEAR_ZERO
			&& proj_k[0] <= c->height + FLOAT_NEAR_ZERO
			&& drr[ri] < hit.t)
			hit = (t_hitrec){p, cone_norm(p, c, proj_k[0], proj_k[1]),
				NULL, drr[ri], false, {.0f, .0f}};
	}
	return (hit);
}

static t_hitrec	find_best_hit(t_vec3 axis, const t_props *c,
	t_ray ray, struct s_lpair limit)
{
	t_vec3		ro_base;
	t_vec3		abc;
	t_hitrec	hit[2];
	float		drr[4];

	hit[1] = (t_hitrec){ftvec3(0), ftvec3(0), NULL, INFINITY, 0, {.0f, .0f}};
	ro_base = ftvec3_minus(ray.origin, c->position);
	abc = fillabc(axis, c, ro_base, ray);
	if (fabs(abc.x) > FLOAT_NEAR_ZERO)
	{
		drr[0] = abc.y * abc.y - 4.0f * abc.x * abc.z;
		if (drr[0] >= 0.0f)
		{
			drr[1] = (-abc.y - sqrtf(drr[0])) / (2.0f * abc.x);
			drr[2] = (-abc.y + sqrtf(drr[0])) / (2.0f * abc.x);
			hit[0] = find_root_hit(drr, ray, limit, c);
			if (hit[0].t != INFINITY)
				hit[1] = hit[0];
		}
	}
	return (hit[1]);
}

static void	set_cone_uv(t_hitrec *best, const t_props *c)
{
	t_vec3	basis[3];
	t_vec3	ortho;
	float	proj;

	ft_cone_basis(best->normal, c->rotation, basis);
	proj = ftvec3_dot(ftvec3_minus(best->hit, c->position), c->rotation);
	ortho = ftvec3_minus(ftvec3_minus(best->hit, c->position),
			ftvec3_multiply(c->rotation, ftvec3(proj)));
	best->uv = (t_uv){0.5f + atan2f(ftvec3_dot(ortho, ftvec3_cross(basis[2],
					basis[0])), ftvec3_dot(ortho, basis[0]))
		/ (2.0f * PI), proj / c->height};
}

/*
	The cone is basicly like a cylinder
	Like the triangle, i reused other members of t_props:
	- position = endpoint of end1
	- rotation = normal of cone
	- radius = radius of end1
*/
uint32_t	ft_cone_hit(t_obj cone, t_ray ray,
	t_hitrec *rec, struct s_lpair limit)
{
	t_props		c;
	t_hitrec	side_hit;
	t_hitrec	cap_hit;
	t_hitrec	best;

	c = cone.props;
	side_hit = find_best_hit(c.rotation, &c, ray, limit);
	cap_hit = find_conecap_hit(c.rotation, &c, ray, limit);
	if (side_hit.t == INFINITY && cap_hit.t == INFINITY)
		return (false);
	if (side_hit.t <= cap_hit.t)
		best = side_hit;
	else
		best = cap_hit;
	if (best.t == side_hit.t && best.t != INFINITY)
		set_cone_uv(&best, &c);
	assign_rayhit(rec, best, &cone.mat);
	ft_hitr_set_face_normal(rec, ray, ftvec3_unit(best.normal));
	return (true);
}
