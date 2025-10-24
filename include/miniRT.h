/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:14:42 by afelger           #+#    #+#             */
/*   Updated: 2025/10/25 16:28:32 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "pseudo_random.h"
# include "MLX42.h"
# include "ftray.h"
# include "ftcolor.h"
# include "ftvec3.h"
# include "dyn_arr.h"
# include "hitable.h"
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>

# define STAN_SAMPLES_PER_PIXEL 1
# define MAX_DEPTH 3
# define MOV_SPEED 0.1
# define PHONG_SHININESS 32.0f
# define MIN_REFLECTION_DROPOUT .05f

struct s_ftray_color_props
{
	t_hitrec	rec;
	t_vec3		next_color;
	t_vec3		view_dir;
	t_vec3		local_color;
	t_vec3		light_acc;
	t_obj		*obj;
};

typedef struct s_camera
{
	t_vec3		center;
	t_vec3		look_at;
	float		fov;
	float		focal_length;
	float		viewport_width;
	float		viewport_height;
	int			image_height;
	int			image_width;
	t_vec3		vupper_left;
	t_vec3		viewport_u;
	t_vec3		viewport_v;
	t_vec3		u;			// Right vector
	t_vec3		v;			// Up vector
	t_vec3		w;			// reverse direction
	t_vec3		delta_u;	// Horizontal vector
	t_vec3		delta_v;	// Vertical vector
	uint32_t	samples_per_pixel;
	t_vec3		vec_up;
	t_vec3		ambient;
	float		ambient_intensity;
}	t_camera;

typedef struct s_camera_p
{
	t_vec3		center;
	t_vec3		look_at;
	float		fov;
	int			image_height;
	int			image_width;
	uint32_t	samples_per_pixel;
	t_vec3		ambient;
	float		ambient_intensity;
}	t_camera_p;

typedef struct s_ray_props
{
	t_vec3	pixel_loc;
	t_vec3	origin;
}	t_ray_props;

typedef struct s_app
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	int32_t		width;
	int32_t		height;
	t_camera	*active_camera;
	t_dyn		hitable;
}	t_app;

int32_t pars_init(int argc, char **argv, t_app *app);
t_vec3		ftray_color(t_ray ray, t_dyn *arr, int depth, float left_reflect);
uint32_t	ft_camera_init(t_camera *camera, t_camera_p props);
void		ft_camera_calc(t_camera *camera);
void		ft_camera_apply(t_camera *cam, t_vec3 apply);
uint32_t	ft_camera_render(t_app *app, void (*put_pixel)(mlx_image_t *image,
					int x, int y, uint32_t color));
void		ftref_lambert(struct s_ftray_color_props *p, t_props *pl,
				t_vec3 to_light);
void		ftref_phong(struct s_ftray_color_props *p, t_props *pl,
				t_vec3 to_light);
#endif /* MINIRT_H */
