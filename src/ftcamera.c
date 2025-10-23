/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftcamera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:54:06 by afelger           #+#    #+#             */
/*   Updated: 2025/10/23 11:27:44 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_camera_apply(t_camera *cam, t_vec3 apply)
{
	cam->look_at = ftvec3_plus(cam->look_at, apply);
	ft_camera_calc(cam);
}

static t_vec3	sample_square(void)
{
	return ((t_vec3){rand_double() - .5, rand_double() - .5, 0});
}

static t_ray	get_rand_ray(t_vec3 pixel_loc, t_vec3 origin, t_camera *cam)
{
	t_vec3	offset;
	t_vec3	sample_pos;

	offset = ftvec3_multiply(sample_square(),
			ftvec3_plus(cam->delta_u, cam->delta_v));
	sample_pos = ftvec3_plus(pixel_loc, offset);
	return (ftray_create(cam->ambient, cam->ambient_intensity,
			origin, ftvec3_minus(sample_pos, origin)));
}

static t_vec3	render_loop(t_app *app, t_vec3 pixel00_loc, float x, float y)
{
	t_vec3		pixel_center;
	t_vec3		color;
	t_vec3		new_col;
	uint32_t	i;

	color = ftvec3(0);
	pixel_center = ftvec3_plus(pixel00_loc,
			ftvec3_plus(
				ftcol_scale(app->active_camera->delta_u, x),
				ftcol_scale(app->active_camera->delta_v, y)));
	i = 0;
	while (i < app->active_camera->samples_per_pixel)
	{
		new_col = ftray_color(get_rand_ray(pixel_center,
					app->active_camera->center, app->active_camera),
				&app->hitable, MAX_DEPTH, 1);
		color = ftvec3_plus(color, ftvec3_multiply(new_col,
					ftvec3(1.0f
						/ (float) app->active_camera->samples_per_pixel)));
		i++;
	}
	return (color);
}

uint32_t	ft_camera_render(t_app *app,
	void (*put_pixel)(mlx_image_t *image, int x, int y, uint32_t color))
{
	t_vec3		pixel00_loc;
	uint32_t	y;
	uint32_t	x;
	t_vec3		color;

	y = 0;
	x = 0;
	pixel00_loc = ftvec3_plus(app->active_camera->vupper_left,
			ftvec3_multiply(ftvec3_plus(app->active_camera->delta_u,
					app->active_camera->delta_v), (t_vec3){0.5, 0.5, 0.5}));
	while (y < app->image->height)
	{
		x = 0;
		while (x < app->image->width)
		{
			color = render_loop(app, pixel00_loc, x, y);
			put_pixel(app->image, x, y, ftvec3_tocolor(color, 1.0));
			x++;
		}
		y++;
	}
	return (0);
}
