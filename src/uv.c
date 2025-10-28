/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:51:08 by afelger           #+#    #+#             */
/*   Updated: 2025/10/27 15:02:27 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "hitable.h"
#include "math.h"
/*
	base[0] = Tangent
	base[1] = Bitangent
	base[2] = Normal back
*/
void	uv_ortho_basis(t_vec3 normal, t_vec3 base[3])
{
	t_vec3	nn;
	t_vec3	a;

	nn = ftvec3_unit(normal);
	if (fabsf(nn.y) < 0.999f)
		a =  (t_vec3){0.f, 1.f, 0.f};
	else
		a = (t_vec3){1.f, 0.f, 0.f};
	base[0] = ftvec3_unit(ftvec3_cross(a, nn));
	base[1] = ftvec3_cross(nn, base[0]);
	base[2] = nn;
}

/*
Reference
https://gamedev.stackexchange.com/questions/114412/how-to-get-uv-coordinates-for-sphere-cylindrical-projection
*/
t_uv	uv_sphere(t_props sphere, t_vec3 p)
{
	t_vec3	normal;
	float	uu;
	float	vv;

	normal = ftvec3_divide(ftvec3_minus(p, sphere.position), ftvec3(sphere.radius));
	uu = 0.5f + atan2f(normal.z, normal.x) / (2.f * PI);
	vv = 0.5f - asinf(normal.y) / PI;
	return ((t_uv){uu, vv});
	//EDIT: The unit_vec is already calculated, because the length of the norm vec is sphere.radius
	//normal = ftvec3_unit(ftvec3_divide(ftvec3_minus(p, sphere.position), ftvec3(sphere.radius)));
	//EDIT: By definition normal can't exceed value of 1 in any direction. 
	//vv = 0.5f - asinf(clamp(normal.y, -1.0f, 1.0f))   / PI;
	//EDIT: The flourf(uu) can't be nothing else then 0.0f
	//return ((t_uv){uu - floorf(uu), clamp(vv, 0.f, 1.0f)});
}

/*
Somwhat of Reference
https://gamedev.stackexchange.com/questions/172352/finding-texture-coordinates-for-plane
but mapping planes is easy, finding a scale for the texture is not
*/
t_uv	uv_plane(t_props plane, t_vec3 p)
{
	t_vec3	basis[3];
	float	uu;
	float	vv;

	uv_ortho_basis(ftvec3_unit(plane.rotation), basis);
	uu = ftvec3_dot(ftvec3_minus(p, plane.position), basis[0]) / 1; // TODO: REPLACE 1 with TextureScale
	vv = ftvec3_dot(ftvec3_minus(p, plane.position), basis[1]) / 1; // TODO: REPLACE 1 with TextureScale
	return ((t_uv){uu - floorf(uu), vv - floorf(vv)});
}

//http://www.raytracerchallenge.com/bonus/texture-mapping.html
t_uv	uv_cylside(t_vec3 axis, t_props cylinder, t_vec3 p)
{
	t_vec3	basis[3];
	t_vec3	uyv;
	t_vec3	q;

	axis = ftvec3_unit(axis);
	uv_ortho_basis(axis, basis);
	uyv.y = ftvec3_dot(ftvec3_minus(p, cylinder.position), axis);
	q = ftvec3_minus(ftvec3_minus(p, cylinder.position), ftcol_scale(axis, uyv.y));
	uyv.x = (atan2f(ftvec3_dot(q, basis[1]), ftvec3_dot(q, basis[0])) + PI) / (2.f * PI);
	uyv.z = (uyv.y / cylinder.height);
	return ((t_uv){uyv.x - floorf(uyv.x), clamp(uyv.z, 0.f, 1.0f)});
}

// Caps can be done by uv_plane
