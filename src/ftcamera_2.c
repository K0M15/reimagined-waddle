/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftcamera_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:11:25 by afelger           #+#    #+#             */
/*   Updated: 2025/10/25 16:27:51 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	handle_pl(struct s_ftray_color_props *p, t_dyn *arr)
{
	t_props		*pl;
	t_vec3		to_light;
	t_hitrec	temp;

	pl = &p->obj->props;
	to_light = ftvec3_minus(pl->position, p->rec.hit);
	if (!world_hit(arr, (t_ray){ftvec3_plus(p->rec.hit, ftvec3_multiply(
					p->rec.normal, ftvec3(FLOAT_NEAR_ZERO))),
			ftvec3_unit(to_light),
			ftvec3(0),
			0
		}, &temp, (struct s_lpair){0.0001, ftvec3_length(to_light) - 1e-4}))
	{
		ftref_lambert(p, pl, to_light);
		ftref_phong(p, pl, to_light);
	}
}

static t_ray	ft_mat_scatter(t_ray inc, t_hitrec *rec)
{
	t_ray	out;

	(void) inc;
	out.origin = rec->hit;
	out.ambient = ftvec3(0);
	if (rand_double() < rec->mat->scatter)
		out.direction = ftvec3_unit(ftvec3_plus(
					ftvec3_ronhemi(rec->normal), rec->normal));
	else
		out.direction = ftvec3_unit(ftvec3_reflect(inc.direction, rec->normal));
	return (out);
}

t_vec3	ftray_color(t_ray ray, t_dyn *arr, int depth, float left_reflect)
{
	struct s_ftray_color_props	p;
	uint32_t					i;

	if (depth <= 0 || left_reflect < MIN_REFLECTION_DROPOUT
		|| !world_hit(arr, ray, &p.rec, (struct s_lpair){MIN_DIST, MAX_DIST}))
		return (ftcol_scale(ray.ambient, ray.ambient_intensity));
	if (p.rec.mat->is_emitting)
		return (p.rec.mat->color);
	p.view_dir = ftvec3_unit(ftvec3_multiply(ray.direction, ftvec3(-1)));
	p.next_color = ftray_color(ft_mat_scatter(ray, &p.rec), arr, depth - 1,
			left_reflect * p.rec.mat->reflectivity);
	p.local_color = ftcol_scale(ray.ambient, ray.ambient_intensity);
	p.light_acc = ftvec3(0);
	i = 0;
	while (i < arr->filled)
	{
		p.obj = &arr->elem[i];
		if (p.obj->type == POINT_LIGHT)
			handle_pl(&p, arr);
		i++;
	}
	return (ftcol_add(ftcol_scale(ftcol_add(p.local_color, p.light_acc),
				1.0f - p.rec.mat->reflectivity),
			ftcol_scale(p.next_color, p.rec.mat->reflectivity)));
}

void	ft_camera_calc(t_camera *camera)
{
	double	h;

	h = tan(degrees_to_rad(camera->fov) / 2);
	camera->focal_length = ftvec3_length(
			ftvec3_minus(camera->center, camera->look_at));
	camera->viewport_height = 2 * h * camera->focal_length;
	camera->viewport_width = camera->viewport_height
		* ((double)camera->image_width / (double)camera->image_height);
	camera->w = ftvec3_unit(ftvec3_minus(camera->center, camera->look_at));
	camera->u = ftvec3_unit(ftvec3_cross(camera->w, camera->vec_up));
	camera->v = ftvec3_cross(camera->w, camera->u);
	camera->viewport_u = ftvec3_multiply(camera->u,
			ftvec3(camera->viewport_width));
	camera->viewport_v = ftvec3_multiply(camera->v,
			ftvec3(camera->viewport_height));
	camera->delta_u = ftvec3_divide(camera->viewport_u,
			ftvec3(camera->image_width));
	camera->delta_v = ftvec3_divide(camera->viewport_v,
			ftvec3(camera->image_height));
	camera->vupper_left = ftvec3_minus(camera->center,
			ftvec3_multiply(ftvec3(camera->focal_length), camera->w));
	camera->vupper_left = ftvec3_minus(camera->vupper_left,
			ftvec3_divide(camera->viewport_u, ftvec3(2)));
	camera->vupper_left = ftvec3_minus(camera->vupper_left,
			ftvec3_divide(camera->viewport_v, ftvec3(2)));
}

uint32_t	ft_camera_init(t_camera *camera, t_camera_p props)
{
	camera->vec_up = (t_vec3){0, 1, 0};
	camera->center = props.center;
	camera->look_at = props.look_at;
	camera->fov = props.fov;
	camera->image_width = props.image_width;
	camera->image_height = props.image_height;
	ft_camera_calc(camera);
	camera->samples_per_pixel = props.samples_per_pixel;
	camera->ambient = props.ambient;
	camera->ambient_intensity = props.ambient_intensity;
	return (0);
}
