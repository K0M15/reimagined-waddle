/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:05:57 by afelger           #+#    #+#             */
/*   Updated: 2025/10/23 11:27:01 by kzarins          ###   ########.fr       */
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
	return (true);
}
