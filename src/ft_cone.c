/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:31:26 by afelger           #+#    #+#             */
/*   Updated: 2025/11/02 18:34:57 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hitable.h"
#include "ftvec3.h"

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

t_hitrec	find_conecap_hit(t_vec3 axis, t_props *c,
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
				result.uv = uv_plane((t_props){
					.position = cap[ci+2],
					.rotation = cap[4],
					.brightness = 0,
					.color = ftvec3(0),
					.diameter = 0,
					.height = 0,
					.radius = 0
				}, result.hit);
			}
	}
	return (result);
}

/*
 For a truncated cone the radius shifts:
  r(m) = r0 + k * m 
  m = axis·(p - position) and k = (r1 - r0)/height
 We compute q0,q1 (perp components) and derive quadratic:
  a = dot(q1,q1) - (k*m1)^2
  b = 2*(dot(q0,q1) - (r0 + k*m0)*k*m1)
  c = dot(q0,q0) - (r0 + k*m0)^2
*/
static t_vec3	fillabc(t_vec3 axis, t_props *c, t_vec3 ro_base, t_ray ray)
{
	t_vec3	abc;
	t_vec3	q0;
	t_vec3	q1;
	float	k;
	
	k = (c->height != 0.0f) ? ((c->diameter * 0.5f - c->radius) / c->height) : 0.0f;
	q0 = ftvec3_minus(ro_base, ftvec3_multiply(axis, ftvec3(ftvec3_dot(ro_base, axis))));
	q1 = ftvec3_minus(ray.direction, ftvec3_multiply(axis, ftvec3(ftvec3_dot(ray.direction, axis))));
	abc.x = ftvec3_dot(q1, q1) - (k * k) * (ftvec3_dot(ray.direction, axis) * ftvec3_dot(ray.direction, axis));
	abc.y = 2.0f * (ftvec3_dot(q0, q1) - (c->radius + k * ftvec3_dot(ro_base, axis)) * (k * ftvec3_dot(ray.direction, axis)));
	abc.z = ftvec3_dot(q0, q0) - (c->radius + k * ftvec3_dot(ro_base, axis)) * (c->radius + k * ftvec3_dot(ro_base, axis));
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

void ft_cone_basis(t_vec3 normal, t_vec3 axis, t_vec3 basis[3])
{
	basis[2] = ftvec3_unit(normal);
	basis[1] = ftvec3_unit(axis);
	basis[0] = ftvec3_unit(ftvec3_cross(basis[1], basis[2]));
}

static t_hitrec	find_best_hit(t_vec3 axis, t_props *c,
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

/*
	The cone is basicly like a cylinder but with 2 diameters, a starting and an ending.
	Like the triangle, i reused other members of t_props:
	- position = endpoint of end1
	- rotation = normal of cone
	- radius = radius of end1
	- diameter = radius*2 of end2
*/
uint32_t	ft_cone_hit(t_obj cone, t_ray ray,
	t_hitrec *rec, struct s_lpair limit)
{
	t_props		c;
	t_vec3		axis;
	t_hitrec	side_hit;
	t_hitrec	cap_hit;
	t_hitrec	best;
	t_vec3		basis[3];

	c = cone.props;
	axis = ftvec3_unit(c.rotation);
	side_hit = find_best_hit(axis, &c, ray, limit);
	cap_hit = find_conecap_hit(axis, &c, ray, limit);
	if (side_hit.t == INFINITY && cap_hit.t == INFINITY)
		return (false);
	if (side_hit.t <= cap_hit.t)
		best = side_hit;
	else
		cap_hit;
	if (best.t == side_hit.t && best.t != INFINITY)
	// {
	//	 ft_cone_basis(best.normal, axis, basis);
	//	 /* compute projection along axis (v) */
	//	 {
	//		 float proj = ftvec3_dot(ftvec3_minus(best.hit, c.position), axis);
	//		 float v = proj / c.height;
	//		 /* compute angle around axis for u */
	//		 t_vec3 ortho = ftvec3_minus(ftvec3_minus(best.hit, c.position),
	//				 ftvec3_multiply(axis, ftvec3(proj)));
	//		 float x = ftvec3_dot(ortho, basis[0]);
	//		 /* use a perpendicular tangent for y */
	//		 t_vec3 tangent_y = ftvec3_cross(basis[2], basis[0]);
	//		 float y = ftvec3_dot(ortho, tangent_y);
	//		 float angle = atan2f(y, x);
	//		 float u = 0.5f + angle / (2.0f * PI);
	//		 best.uv = (t_uv){u, v};
	//	 }
	// }
	assign_rayhit(rec, best, &cone.mat);
	ft_hitr_set_face_normal(rec, ray, ftvec3_unit(best.normal));
	return (true);
}