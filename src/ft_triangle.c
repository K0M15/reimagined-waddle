/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triangle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 15:06:16 by afelger           #+#    #+#             */
/*   Updated: 2025/11/04 17:09:26 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hitable.h"
#include "ftvec3.h"

struct s_tri_val{
	t_vec3	h;
	t_vec3	s;
	t_vec3	q;
	t_uv	uv;
	float	det;
	float	invdet;
	float	t;
};

t_vec3	ft_tri_norm(t_obj tri)
{
    t_vec3 v2;
	v2 = (t_vec3){tri.props.radius, tri.props.diameter, tri.props.height};
    return (ftvec3_normalize(ftvec3_cross(ftvec3_minus(tri.props.rotation, tri.props.position), ftvec3_minus(v2, tri.props.position))));
}

t_vec3 ft_tri_middle(t_obj tri){
	t_vec3	vert1, vert2, vert3;

	vert1 = tri.props.position;
	vert2 = tri.props.rotation;
	vert3 = (t_vec3){tri.props.radius, tri.props.diameter, tri.props.height};
	return ((t_vec3){
		(vert1.x + vert2.x + vert3.x) / 3.f,
		(vert1.y + vert2.y + vert3.y) / 3.f,
		(vert1.z + vert2.z + vert3.z) / 3.f
	});
}

/*
	In a triangle the props map different, to avoid memory creep
	color = color
	position = vertex1
	rotation = vertex2
	radius = vertex3.x
	diameter = vertex3.y
	height = vertex3.z

*/
uint32_t ft_tri_hit(t_obj triangle, t_ray ray,
    t_hitrec *rec, struct s_lpair limit)
{
    t_vec3 edge[2];
    t_vec3 v[3];
    struct s_tri_val s; 
    
    v[0] = triangle.props.position;
    v[1] = triangle.props.rotation;
    v[2] = (t_vec3){triangle.props.radius, triangle.props.diameter, triangle.props.height};
    edge[0] = ftvec3_minus(v[1], v[0]);
    edge[1] = ftvec3_minus(v[2], v[0]);
    s.h = ftvec3_cross(ray.direction, edge[1]);
    s.det = ftvec3_dot(edge[0], s.h);
    if (fabsf(s.det) < FLOAT_NEAR_ZERO)
        return (false);
    s.invdet = 1.0f / s.det;
    s.s = ftvec3_minus(ray.origin, v[0]);
    s.uv.u = s.invdet * ftvec3_dot(s.s, s.h);
    if (s.uv.u < 0.0f || s.uv.u > 1.0f)
        return (false);
    s.q = ftvec3_cross(s.s, edge[0]);
    s.uv.v = s.invdet * ftvec3_dot(ray.direction, s.q);
    if (s.uv.v < 0.0f || s.uv.u + s.uv.v > 1.0f)
        return (false);
    s.t = s.invdet * ftvec3_dot(edge[1], s.q);
    if (s.t < limit.min || s.t > limit.max)
        return (false);
    rec->t = s.t;
    rec->hit = ftray_at(ray, s.t);
    rec->mat = &triangle.mat;
    ft_hitr_set_face_normal(rec, ray, ftvec3_normalize(ftvec3_cross(edge[0], edge[1])));
    rec->uv = (t_uv){s.uv.u, s.uv.v};
    return (true);
}
