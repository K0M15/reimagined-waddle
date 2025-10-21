/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:07:04 by afelger           #+#    #+#             */
/*   Updated: 2025/10/21 17:17:53 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hitable.h"
#include "ftvec3.h"

t_obj	ft_cylinder_create(t_cylinder_p params, t_material *mat)
{
	t_obj	cyl;

	cyl.type = ERROR;
	cyl.props = malloc(sizeof(t_cylinder_p));
	if (!cyl.props)
		return (cyl);
	cyl.type = CYLINDER;
	cyl.mat = mat;
	memcpy(cyl.props, &params, sizeof(t_cylinder_p));
	((t_cylinder_p *)cyl.props)->rotation
		= ftvec3_unit(((t_cylinder_p *)cyl.props)->rotation);
	return (cyl);
}

static t_vec3	fillabc(t_vec3 axis, t_cylinder_p *c, t_vec3 ro_base, t_ray ray)
{
	t_vec3	abc;

	abc.x = ftvec3_dot(ftvec3_minus(ray.direction, ftvec3_multiply(axis,
					ftvec3(ftvec3_dot(ray.direction, axis)))),
			ftvec3_minus(ray.direction, ftvec3_multiply(axis, ftvec3(
						ftvec3_dot(ray.direction, axis)))));
	abc.y = 2.0f * ftvec3_dot(ftvec3_minus(ray.direction, ftvec3_multiply(
					axis, ftvec3(ftvec3_dot(ray.direction, axis)))),
			ftvec3_minus(ro_base, ftvec3_multiply(axis, ftvec3(
						ftvec3_dot(ro_base, axis)))));
	abc.z = ftvec3_dot(ftvec3_minus(ro_base, ftvec3_multiply(axis, ftvec3(
						ftvec3_dot(ro_base, axis)))), ftvec3_minus(ro_base,
				ftvec3_multiply(axis, ftvec3(ftvec3_dot(ro_base, axis)))))
		- c->radius * c->radius;
	return (abc);
}

t_hitrec	find_root_hit(float drr[3], t_ray ray,
	struct s_lpair limit, t_cylinder_p *c)
{
	t_vec3		p;
	t_hitrec	hit;
	float		proj;
	int			ri;

	ri = 1;
	hit = (t_hitrec){ftvec3(0), ftvec3(0), NULL, INFINITY, 0};
	while (ri < 2)
	{
		if (!(drr[ri] > limit.min && drr[ri] < limit.max))
			continue ;
		p = ftray_at(ray, drr[ri]);
		proj = ftvec3_dot(ftvec3_minus(p, c->position),
				ftvec3_unit(c->rotation));
		if (proj >= 0.0f - FLOAT_NEAR_ZERO
			&& proj <= c->height + FLOAT_NEAR_ZERO
			&& drr[ri] < hit.t)
			hit = (t_hitrec){p, ftvec3_unit(
					ftvec3_minus(ftvec3_minus(p, c->position), ftvec3_multiply(
							ftvec3_unit(c->rotation), ftvec3(proj)))),
				NULL, drr[ri], false};
		ri++;
	}
	return (hit);
}

//drr: 0 = disk, 1,2 = roots
t_hitrec	find_best_hit(t_vec3 axis, t_cylinder_p *c,
	t_ray ray, struct s_lpair limit)
{
	t_vec3		ro_base;
	t_vec3		abc;
	t_hitrec	hit[2];
	float		drr[4];

	hit[1] = (t_hitrec){ftvec3(0), ftvec3(0), NULL, INFINITY, 0};
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

t_hitrec	find_cap_hit(t_vec3 axis, t_cylinder_p *c,
	t_ray ray, struct s_lpair limit)
{
	t_vec3		cap[4];
	t_hitrec	result;
	double		tcap;
	int			ci;

	cap[0] = c->position;
	cap[1] = ftvec3_plus(c->position, ftvec3_multiply(axis, ftvec3(c->height)));
	cap[2] = ftvec3_multiply(axis, ftvec3(-1.0f));
	cap[3] = axis;
	result = (t_hitrec){ftvec3(0), ftvec3(0), NULL, INFINITY, 0};
	ci = -1;
	while (++ci < 2)
	{
		if (fabs(ftvec3_dot(axis, ray.direction)) < FLOAT_NEAR_ZERO)
			continue ;
		tcap = ftvec3_dot(axis, ftvec3_minus(cap[ci], ray.origin))
			/ ftvec3_dot(axis, ray.direction);
		if (!(tcap > limit.min && tcap < limit.max))
			continue ;
		if (ftvec3_dot(ftvec3_minus(ftvec3_minus(ftray_at(ray, tcap), cap[ci]),
					ftvec3_multiply(axis, ftvec3(ftvec3_dot(ftvec3_minus(
									ftray_at(ray, tcap), cap[ci]), axis)))),
				ftvec3_minus(ftvec3_minus(ftray_at(ray, tcap), cap[ci]),
					ftvec3_multiply(axis, ftvec3(ftvec3_dot(ftvec3_minus(
									ftray_at(ray, tcap), cap[ci]), axis)))))
			<= c->radius * c->radius + 1e-6f)
			if (tcap < result.t)
				result = (t_hitrec){ftray_at(ray, tcap), cap[ci + 2],
					NULL, tcap, false};
	}
	return (result);
}

uint32_t	ft_cylinder_hit(t_obj cyl, t_ray ray,
	t_hitrec *rec, struct s_lpair limit)
{
	t_cylinder_p	*c;
	t_vec3			axis;
	t_hitrec		best_hit[2];

	c = (t_cylinder_p *)cyl.props;
	axis = ftvec3_unit(c->rotation);
	best_hit[0] = find_best_hit(axis, c, ray, limit);
	best_hit[1] = find_cap_hit(axis, c, ray, limit);
	if (best_hit[0].t == INFINITY && best_hit[1].t == INFINITY)
		return (false);
	if (best_hit[0].t > best_hit[1].t)
		best_hit[0] = best_hit[1];
	assign_rayhit(rec, best_hit[0], cyl.mat);
	ft_hitr_set_face_normal(rec, ray, ftvec3_unit(best_hit[0].normal));
	return (true);
}
