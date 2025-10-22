/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:07:04 by afelger           #+#    #+#             */
/*   Updated: 2025/10/22 17:45:58 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hitable.h"
#include "ftvec3.h"

struct s_cylfuncp
{
	t_props *c;
	t_vec3 axis;
};

// t_obj	ft_cylinder_create(t_cylinder_p params, t_material *mat)
// {
// 	t_obj	cyl;

// 	cyl.type = ERROR;
// 	if(!(cyl.props = malloc(sizeof(t_cylinder_p))))
// 		return cyl;
// 	cyl.type = CYLINDER;
// 	cyl.mat = mat;
// 	memcpy(cyl.props, &params, sizeof(t_cylinder_p));
// 	((t_cylinder_p*) cyl.props)->rotation = ftvec3_unit(((t_cylinder_p*) cyl.props)->rotation);
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
			ftvec3_multiply(axis, ftvec3( ftvec3_dot(ro_base, axis)))))
			- c->radius * c->radius;
	return (abc);
}

uint32_t	ft_cylinder_hit(t_obj cyl, t_ray ray, t_hitrec *rec, struct s_lpair limit)
{
	t_props *c = (t_props *)&cyl.props;
	t_vec3 axis = ftvec3_unit(c->rotation);
	t_vec3 ro_base = ftvec3_minus(ray.origin, c->position);

	t_vec3 abc = fillabc(axis, c, ro_base, ray);
	double best_t = INFINITY;
	t_vec3 best_hit = ftvec3(0);
	t_vec3 best_normal = ftvec3(0);

	if (fabs(abc.x) > FLOAT_NEAR_ZERO)
	{
		float disc = abc.y * abc.y - 4.0f * abc.x * abc.z;
		if (disc >= 0.0f)
		{
			float sd = sqrtf(disc);
			float t0 = (-abc.y - sd) / (2.0f * abc.x);
			float t1 = (-abc.y + sd) / (2.0f * abc.x);
			float roots[2] = { t0, t1 };
			for (int ri = 0; ri < 2; ++ri)
			{
				double t = roots[ri];
				if (!(t > limit.min && t < limit.max))
					continue;
				t_vec3 p = ftray_at(ray, t);
				float proj = ftvec3_dot(ftvec3_minus(p, c->position), axis);
				if (proj >= 0.0f - FLOAT_NEAR_ZERO && proj <= c->height + FLOAT_NEAR_ZERO)
				{
					if (t < best_t)
					{
						best_t = t;
						best_hit = p;
						t_vec3 out = ftvec3_minus(ftvec3_minus(p, c->position), ftvec3_multiply(axis, ftvec3(proj)));
						best_normal = ftvec3_unit(out);
					}
				}
			}
		}
	}
	//abc end
	t_vec3 cap_centers[2] = { c->position, ftvec3_plus(c->position, ftvec3_multiply(axis, ftvec3(c->height))) };
	t_vec3 cap_normals[2] = { ftvec3_multiply(axis, ftvec3(-1.0f)), axis };
	int ci = 0;
	while (ci < 2)
	{
		t_vec3 cc = cap_centers[ci];
		t_vec3 cn = cap_normals[ci];
		float denom = ftvec3_dot(axis, ray.direction);
		if (fabs(denom) < FLOAT_NEAR_ZERO)
		{
			ci++;
			continue;
		}
		double tcap = ftvec3_dot(axis, ftvec3_minus(cc, ray.origin)) / denom;
		if (!(tcap > limit.min && tcap < limit.max))
		{
			ci++;
			continue;
		}
		t_vec3 pcap = ftray_at(ray, tcap);
		t_vec3 vrad = ftvec3_minus(ftvec3_minus(pcap, cc), ftvec3_multiply(axis, ftvec3(ftvec3_dot(ftvec3_minus(pcap, cc), axis))));
		float dist2 = ftvec3_dot(vrad, vrad);
		if (dist2 <= c->radius * c->radius + 1e-6f)
		{
			if (tcap < best_t)
			{
				best_t = tcap;
				best_hit = pcap;
				best_normal = cn;
			}
		}
		ci++;
	}

	if (best_t == INFINITY)
		return (false);
	rec->t = best_t;
	rec->hit = best_hit;
	rec->mat = &cyl.mat;
	ft_hitr_set_face_normal(rec, ray, ftvec3_unit(best_normal));
	return (true);
}

