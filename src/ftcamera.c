/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftcamera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:54:06 by afelger           #+#    #+#             */
/*   Updated: 2025/10/29 15:38:10 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//The movements have to get corrected base on the current camera vector rotation
//+z = forward
//+x = right
void	ft_camera_move(t_camera *cam, t_vec3 move)
{
	t_vec3	move_vec;

	if (move.z)
		move_vec = ftvec3_multiply(cam->look_at, ftvec3(move.z));
	if (move.x)
		move_vec = ftvec3_multiply(cam->u, ftvec3(move.x));
	move_vec.z = 0;
	printf("---------\n");
	//printf("The camera cam->u: X%f Y%f Z%f\n", cam->u.x, cam->u.y, cam->u.z);
	//printf("The move move: X%f Y%f Z%f\n", move.x, move.y, move.z);
	printf("The camera_center(before): X%f Y%f Z%f\n", cam->center.x, cam->center.y, cam->center.z);
	//cam->center = ftvec3_plus(cam->center,move_vec);
	cam->center = ftvec3_plusp(cam->center, move_vec);
	//cam->center.z -= move_vec.z;
	printf("The camera_center: X%f Y%f Z%f\n", cam->center.x, cam->center.y, cam->center.z);
	printf("---------\n");
	cam->look_at = ftvec3_unit(ftvec3_plus(cam->look_at, move_vec));
	//cam->vec_up = ftvec3_plus(cam->vec_up, move_vec);
	ft_camera_calc(cam);
}

void	ft_camera_apply(t_camera *cam, t_vec3 apply)
{
	t_vec3	dir;
	t_vec3	right;

	dir = ftvec3_unit(ftvec3_minus(cam->look_at, cam->center));
	if (ftvec3_length(dir) <= FLOAT_NEAR_ZERO)
		return ;
	if (apply.x != 0.0f)
		dir = ftvec3_unit(rotate_axis(dir, cam->vec_up, apply.x));
	right = ftvec3_unit(ftvec3_cross(cam->vec_up, dir));
	if (apply.y != 0.0f && fabsf(ftvec3_dot(ftvec3_unit(rotate_axis(dir,
						right, -apply.y)), cam->vec_up)) < 0.995f)
		dir = ftvec3_unit(rotate_axis(dir, right, -apply.y));
	cam->look_at = ftvec3_plus(cam->center,
			ftcol_scale(dir, ftvec3_length(dir)));
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
	void (*put_pixel)(mlx_image_t *image, int x, int y, uint32_t color),
	uint32_t start, uint32_t end)
{
	t_vec3		pixel00_loc;
	uint32_t	y;
	uint32_t	x;
	t_vec3		color;

	y = start / app->image->width;
	x = start % app->image->width;
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
		if (x * y > end)
			break ;
	}
	return (x * y);
}
