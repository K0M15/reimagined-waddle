/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:51:08 by afelger           #+#    #+#             */
/*   Updated: 2025/10/23 11:05:00 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "hitable.h"
#include "math.h"

t_uv	uv_sphere(t_props sphere, t_vec3 p)
{
	t_vec3	normal;
	float	uu;
	float	vv;

	normal = ftvec3_unit(ftvec3_divide(ftvec3_minus(p, sphere.position), ftvec3(sphere.radius)));
	uu = 0.5f + atan2f(normal.z, normal.x) / (2.f * PI);
	vv = 0.5f - asinf(clamp01(normal.y))   / PI;
	return ((t_uv){uu - floorf(uu), clamp(vv, 0.f, 1.0f)});
}

t_uv	uv_plane(t_props plane, t_vec3 p)
{
	
}

t_uv	uv_cylside(t_props cylinder, t_vec3 p)
{
	
}

t_uv	uv_cylcap(t_props cylinder, t_vec3 p)
{
	
}


