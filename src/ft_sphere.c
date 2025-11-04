/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:08:01 by afelger           #+#    #+#             */
/*   Updated: 2025/11/03 16:17:41 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hitable.h"
#include "ftvec3.h"

/*
	Build tangent frame aligned to UV mapping:
	(T)anget = points from east to west
	(B)itanget = north to south
*/
static void	sphere_uv_tangent_basis(t_vec3 n, t_vec3 *T, t_vec3 *B)
{
	t_uv	coords;

	n = ftvec3_unit(n);
	coords.u = atan2f(n.z, n.x);
	coords.v = asinf(fmaxf(-1.f, fminf(1.f, n.y)));
	*T = ftvec3_unit((t_vec3){-cosf(coords.v)
			* sinf(coords.u), 0.0f, cosf(coords.v) * cosf(coords.u)});
	*B = ftvec3_unit((t_vec3){sinf(coords.v) * cosf(coords.u),
			-cosf(coords.v), sinf(coords.v) * sinf(coords.u)});
}

static	void	ft_sphere_uvnormal(t_hitrec *rec, t_obj *sphere)
{
	t_vec3	ngeo[4];
	t_uv	height;
	t_vec3	result;

	rec->uv = uv_sphere(sphere->props, rec->hit);
	if (!sphere->mat.bump)
		return ;
	ngeo[0] = ftvec3_divide(
			ftvec3_minus(rec->hit, sphere->props.position),
			ftvec3(sphere->props.radius));
	sphere_uv_tangent_basis(ngeo[0], &ngeo[1], &ngeo[2]);
	height = interpolate_height(sphere->mat.bump, (t_uv){rec->uv.u, rec->uv.v});
	ngeo[3] = (t_vec3){height.u * ngeo[1].x + height.v * ngeo[2].x,
		height.u * ngeo[1].y + height.v * ngeo[2].y,
		height.u * ngeo[1].z + height.v * ngeo[2].z};
	result = ftvec3_unit((t_vec3){ngeo[0].x - SPHERE_BUMP_STRENGTH * ngeo[3].x,
			ngeo[0].y - SPHERE_BUMP_STRENGTH * ngeo[3].y,
			ngeo[0].z - SPHERE_BUMP_STRENGTH * ngeo[3].z
		});
	if (rec->front_face)
		rec->normal = result;
	else
		rec->normal = ftvec3_multiply(result, ftvec3(-1));
}

static float	ft_sphere_root(float discriminant,
	t_vec3 abc, struct s_lpair limit)
{
	float	root1;
	float	root2;

	root1 = (abc.y - discriminant) / abc.x;
	root2 = (abc.y + discriminant) / abc.x;
	if (root1 > limit.min && root1 < limit.max)
		return (root1);
	else if (root2 > limit.min && root2 < limit.max)
		return (root2);
	return (INFINITY);
}

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
	root = ft_sphere_root(discriminant, abc, limit);
	if (root == INFINITY)
		return (false);
	rec->t = root;
	rec->hit = ftray_at(ray, root);
	ft_hitr_set_face_normal(rec, ray, ftvec3_divide(ftvec3_minus(rec->hit,
				sphere.props.position),
			ftvec3(sphere.props.radius)));
	return (ft_sphere_uvnormal(rec, &sphere), true);
}
