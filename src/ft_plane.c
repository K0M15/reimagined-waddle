/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:05:57 by afelger           #+#    #+#             */
/*   Updated: 2025/10/27 15:24:11 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hitable.h"
#include "ftvec3.h"

// t_obj	ft_plane_create(t_plane_p params, t_material *mat)
// {
// 	t_obj	plane;

// 	plane.type = ERROR;
// 	plane.props = malloc(sizeof(t_plane_p));
// 	if (!plane.props)
// 		return (plane);
// 	plane.type = PLANE;
// 	plane.mat = mat;
// 	memcpy(plane.props, &params, sizeof(t_plane_p));
// 	return (plane);
// }

static void ft_plane_uvnormal(t_hitrec *rec, t_obj *plane)
{
	t_vec3	ngeo[4];
	t_uv	height;

	uv_plane(plane->props, rec->hit);
	if (!plane->mat.bump)
		return;
	uv_ortho_basis(plane->props.rotation, ngeo);
	height = interpolate_height(plane->mat.bump, rec->uv);
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

uint32_t	ft_plane_hit(t_obj plane, t_ray ray, t_hitrec *rec,
	struct s_lpair limit)
{
	t_props	*props;
	double	denom;
	double	d;

	props = (t_props *)&plane.props;
	denom = ftvec3_dot(ftvec3_unit(props->rotation), ray.direction);
	if (fabs(denom) < DOUBLE_NEAR_ZERO)
		return (false);
	d = ftvec3_dot(ftvec3_unit(props->rotation), props->position);
	denom = (d - ftvec3_dot(ftvec3_unit(props->rotation), ray.origin)) / denom;
	if (denom < limit.min || denom > limit.max)
		return (false);
	rec->t = denom;
	rec->hit = ftray_at(ray, denom);
	rec->mat = &plane.mat;
	ft_hitr_set_face_normal(rec, ray, ftvec3_unit(props->rotation));
	ft_plane_uvnormal(rec, &plane);
	return (true);
}
