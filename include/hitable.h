/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:43:59 by afelger           #+#    #+#             */
/*   Updated: 2025/10/23 10:56:06 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITABLE_H
# define HITABLE_H

# include "dyn_arr.h"
# include <stdint.h>
# include <stdlib.h>
# include "ftray.h"
# include "ftvec3.h"
# include "object.h"

typedef struct s_ray t_ray;
# define MIN_DIST 0.001
# define MAX_DIST 1000
# define PI 3.14159265358979323846f

// typedef struct s_sphere_p
// {
// 	float	radius;
// 	t_vec3	position;
// }	t_sphere_p;

// typedef struct s_cylinder_p{
//     float diameter;
//     float height;
//     t_vec3 position;
//     t_vec3 rotation;
// 	t_vec3	color;
// }   t_cylinder_p;

// typedef struct s_plane_p
// {
// 	t_vec3	position;
// 	t_vec3	rotation;
// }	t_plane_p;

// typedef struct s_point_light_p
// {
// 	t_vec3	position;
// 	float	brightness;
// 	t_vec3	color;
// }	t_point_light_p;

typedef struct s_uv
{
	float	u;
	float	v;
}	t_uv;

typedef struct s_hitrec
{
	t_vec3		hit;
	t_vec3		normal;
	t_material	*mat;
	double		t;
	bool		front_face;
	t_uv		uv
}	t_hitrec;

struct s_world_hit_props
{
	t_hitrec	temp;
	uint32_t	ctr;
	uint32_t	hit;
	double		closest;
	t_obj		*obj;
};

struct s_cylfuncp
{
	t_props	*c;
	t_vec3			axis;
};

struct s_lpair
{
	double	min;
	double	max;
};


// t_obj		ft_sphere_create(t_sphere_p params, t_material *mat);
uint32_t	ft_sphere_hit(t_obj sphere, t_ray ray, t_hitrec *rec,
				struct s_lpair limit);
// t_obj		ft_cylinder_create(t_cylinder_p params, t_material *mat);
uint32_t	ft_cylinder_hit(t_obj cyl, t_ray ray, t_hitrec *rec,
				struct s_lpair limit);
// t_obj		ft_plane_create(t_plane_p params, t_material *mat);
uint32_t	ft_plane_hit(t_obj plane, t_ray ray, t_hitrec *rec,
				struct s_lpair limit);
// t_obj		ft_light_create(t_point_light_p props);
void		ft_obj_dest(t_obj sphere);
uint32_t	world_hit(t_dyn *world, t_ray ray, t_hitrec *rec,
				struct s_lpair limit);
void		ft_hitr_set_face_normal(t_hitrec *rec, t_ray ray,
				t_vec3 outwar_norm);
void		assign_rayhit(t_hitrec *rec, t_hitrec src, t_material *material);
t_hitrec	find_cap_hit(t_vec3 axis, t_props *c,
				t_ray ray, struct s_lpair limit);
			
t_uv		uv_sphere(t_props sphere, t_vec3 p);
t_uv		uv_plane(t_props plane, t_vec3 p);
t_uv		uv_cylside(t_props cylinder, t_vec3 p);
t_uv		uv_cylcap(t_props cylinder, t_vec3 p);

#endif /* HITABLE_H */
