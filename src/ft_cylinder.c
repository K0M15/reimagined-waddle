/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:07:04 by afelger           #+#    #+#             */
/*   Updated: 2025/10/28 14:41:12 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hitable.h"
#include "ftvec3.h"

// t_obj	ft_cylinder_create(s_props params, t_material *mat)
// {
// 	t_obj	cyl;

// 	cyl.type = ERROR;
// 	if(!(cyl.props = malloc(sizeof(s_props))))
// 		return cyl;
// 	cyl.type = CYLINDER;
// 	cyl.mat = mat;
// 	memcpy(cyl.props, &params, sizeof(s_props));
// 	((s_props*) cyl.props)->rotation = ftvec3_unit(((s_props*) cyl.props)->rotation);
// 	return (cyl);
// }

static t_vec3	fillabc(t_vec3 axis, t_props *c, t_vec3 ro_base, t_ray ray)
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
	struct s_lpair limit, t_props *c)
{
	t_vec3		p;
	t_hitrec	hit;
	float		proj;
	int			ri;

	ri = 0;
	hit = (t_hitrec){ftvec3(0), ftvec3(0), NULL, INFINITY, 0, (t_uv){0.0f, 0.0f}};
	while (++ri < 2)
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
				NULL, drr[ri], false, {.0f, .0f}};
	}
	return (hit);
}

void ft_cyl_basis(t_vec3 normal, t_vec3 axis, t_vec3 basis[3])
{
	basis[2] = ftvec3_unit(normal);
	basis[1] = ftvec3_unit(axis);
	basis[0] = ftvec3_unit(ftvec3_cross(basis[1], basis[2]));
}

void ft_cyl_uvnormal(t_hitrec *rec, t_vec3 axis, t_obj *cyl)
{
	// get base
	// sample height according to base
	// put stuff into ray, 
	t_vec3	ngeo[4];
	t_uv	height;

	rec->uv = uv_cylside(axis, cyl->props, rec->hit);
	if (!cyl->mat.bump)
		return;
	ft_cyl_basis(cyl->props.rotation, axis, ngeo); // replace with custom base
	height = interpolate_height(cyl->mat.bump, rec->uv);
	ngeo[3] = (t_vec3){height.u * ngeo[0].x + height.v * ngeo[1].x,
		height.u * ngeo[0].y + height.v * ngeo[1].y,
		height.u * ngeo[0].z + height.v * ngeo[1].z};
	rec->normal = ftvec3_unit((t_vec3){ngeo[2].x - SPHERE_BUMP_STRENGTH * ngeo[3].x,
            ngeo[2].y - SPHERE_BUMP_STRENGTH * ngeo[3].y,
            ngeo[2].z - SPHERE_BUMP_STRENGTH * ngeo[3].z
        });
	if (!rec->front_face)
		rec->normal = ftvec3_multiply(rec->normal, ftvec3(-1));
}

//drr: 0 = disk, 1,2 = roots
t_hitrec	find_best_hit(t_vec3 axis, t_props *c,
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

uint32_t	ft_cylinder_hit(t_obj cyl, t_ray ray,
	t_hitrec *rec, struct s_lpair limit)
{
	t_props		c;
	t_vec3		axis;
	t_hitrec	best_hit[2];

	c = cyl.props;
	axis = ftvec3_unit(c.rotation);
	best_hit[0] = find_best_hit(axis, &c, ray, limit);
	best_hit[1] = find_cap_hit(axis, &c, ray, limit);
	if (best_hit[0].t == INFINITY && best_hit[1].t == INFINITY)
		return (false);
	if (best_hit[1].t != INFINITY && best_hit[0].t > best_hit[1].t)
		best_hit[0] = best_hit[1];
	else
		ft_cyl_uvnormal(&best_hit[0], axis, &cyl);
	assign_rayhit(rec, best_hit[0], &cyl.mat);
	ft_hitr_set_face_normal(rec, ray, ftvec3_unit(best_hit[0].normal));
	return (true);
}
