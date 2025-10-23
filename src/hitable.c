/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:54:06 by afelger           #+#    #+#             */
/*   Updated: 2025/10/23 15:55:41 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_hitr_set_face_normal(t_hitrec *rec, t_ray ray, t_vec3 outwar_norm)
{
	rec->front_face = ftvec3_dot(ray.direction, outwar_norm) < 0;
	if (rec->front_face)
		rec->normal = outwar_norm;
	else
		rec->normal = ftvec3_multiply(outwar_norm, ftvec3(-1));
}

void	ft_obj_dest(t_obj obj)
{
	// we dont destroy
	(void) obj;
}

void	assign_rayhit(t_hitrec *rec, t_hitrec src, t_material *material)
{
	rec->hit = src.hit;
	rec->normal = src.normal;
	rec->t = src.t;
	rec->mat = material;
}

// TODO: work on nudge -> 
// https://stackoverflow.com/questions/41211892/
// ray-tracer-artifacts-with-reflection
uint32_t	world_hit(t_dyn *world, t_ray ray,
	t_hitrec *rec, struct s_lpair limit)
{
	struct s_world_hit_props	p;

	p.ctr = 0;
	p.hit = 0;
	p.closest = INFINITY;
	while (p.ctr < world->filled)
	{
		p.obj = &world->elem[p.ctr];
		p.hit = 0;
		if (p.obj->type == SPHERE)
			p.hit = ft_sphere_hit(*p.obj, ray, &p.temp, limit);
		else if (p.obj->type == PLANE)
			p.hit = ft_plane_hit(*p.obj, ray, &p.temp, limit);
		else if (p.obj->type == CYLINDER)
			p.hit = ft_cylinder_hit(*p.obj, ray, &p.temp, limit);
		if (p.hit && p.temp.t < p.closest)
		{
			p.closest = p.temp.t;
			assign_rayhit(rec, p.temp, &p.obj->mat);
		}
		p.ctr++;
	}
	return (p.closest != INFINITY);
}
