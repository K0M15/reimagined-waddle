/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:08:01 by afelger           #+#    #+#             */
/*   Updated: 2025/10/22 17:11:36 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hitable.h"
#include "ftvec3.h"

//t_obj	ft_sphere_create(t_sphere_p params, t_material *mat)
//{
//	t_obj	sphere;
//
//	sphere.type = ERROR;
//	sphere.props = malloc(sizeof(t_sphere_p));
//	if (!sphere.props)
//		return (sphere);
//	sphere.type = SPHERE;
//	sphere.mat = mat;
//	memcpy(sphere.props, &params, sizeof(t_sphere_p));
//	return (sphere);
//}

uint32_t	ft_sphere_hit(t_obj sphere, t_ray ray, t_hitrec *rec,
	struct s_lpair limit)
{
	t_vec3	oc;
	t_vec3	abc;
	float	discriminant;
	float	root;

	oc = ftvec3_minus(sphere.props.position, ray.origin);
	abc = (t_vec3){ftvec3_dot(ray.direction, ray.direction),
		ftvec3_dot(ray.direction, oc),
		ftvec3_dot(oc, oc) - sphere.props.radius
		* sphere.props.radius
	};
	if ((abc.y * abc.y - abc.x * abc.z) < 0)
		return (false);
	discriminant = sqrtf((abc.y * abc.y - abc.x * abc.z));
	root = (abc.y - discriminant) / abc.x;
	if ((root <= limit.min || limit.max <= root)
		&& (((abc.y + discriminant) / abc.x) <= limit.min
		|| limit.max <= ((abc.y + discriminant) / abc.x)))
		return (false);
	rec->t = root;
	rec->hit = ftray_at(ray, root);
	ft_hitr_set_face_normal(rec, ray, ftvec3_divide(ftvec3_minus(rec->hit,
				sphere.props.position),
			ftvec3(sphere.props.radius)));
	return (true);
}
