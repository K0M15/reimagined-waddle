/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:14:42 by afelger           #+#    #+#             */
/*   Updated: 2025/10/10 13:18:53 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H
# include "pseudo_random.h"
# include "MLX42.h"
# include "ftray.h"
# include "ftvec3.h"
# include "dyn_arr.h"
# include "hitable.h"
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>

# define STAN_SAMPLES_PER_PIXEL 1
# define MAX_DEPTH 3
# define MOV_SPEED 0.01

typedef struct s_camera
{
    t_vec3 center;
    t_vec3 look_at;
    float fov;
    float focal_length;
    float viewport_width;
    float viewport_height;
    int image_height;
    int image_width;
    t_vec3 vupper_left;
    t_vec3 viewport_u;
    t_vec3 viewport_v;
    t_vec3 u;           // Right vector
    t_vec3 v;           // Up vector
    t_vec3 w;           // reverse direction
    t_vec3 delta_u;     // Horizontal vector
    t_vec3 delta_v;     // Vertical vector
    uint32_t samples_per_pixel;
    t_vec3 vec_up;
    t_vec3 ambient;
}   t_camera;

typedef struct s_camera_p{
    t_vec3 center;
    t_vec3 look_at;
    float fov;
    int imageHeight;
    int imageWidth;
    uint32_t samples_per_pixel;
    t_vec3 ambient;
}   t_camera_p;

typedef struct s_ray_props{
    t_vec3 pixel_loc;
    t_vec3 origin;
}   t_ray_props;

typedef struct s_app
{
	mlx_t *mlx;
	mlx_image_t *image;
    int32_t width;
    int32_t height;
    t_camera *active_camera;
    t_dyn   hitable;
}	t_app;

int32_t pars_init(int argc, char **argv);

t_vec3 ftray_color(t_ray ray, t_dyn *arr, int depth);
uint32_t ft_camera_init(t_camera *camera, t_camera_p props);
void ft_camera_calc(t_camera *camera);
void ft_camera_apply(t_camera *cam, t_vec3 apply);
uint32_t ft_camera_render(
    t_app *app,
    void (*put_pixel)(mlx_image_t *image, int x, int y, uint32_t color));

//TODO: Make it cleaner

#include "elements.h"
#include "ft_ll.h"

//typedef struct s_scene {
//	t_ambient_light	*ambient_light;
//	t_camera 	*camera;
//	t_light		*light;
//	t_sphere	*sphere;
//	t_plane		*plane;
//	t_cylinder	*cylinder;
//} t_scene;

//The global settings for the viewport
typedef struct	s_settings {
	FLOAT	viewport_height;
	FLOAT	viewport_width;
	t_vec3	pixel_delta_h;
	t_vec3	pixel_delta_w;
	t_point	viewport_left;
	t_point	first_pixel;
} t_settings;

//Because C compiles in row major order the order is pixel[y][x]
//Pixels should be stored with values from 0 - 255
typedef struct s_scene {
	t_rgb	pixels[IMAGE_HEIGHT][IMAGE_WIDTH];
	t_node	*ambient_light;
	t_node 	*camera;
	t_node	*light;
	t_node	*sphere;
	t_node	*plane;
	t_node	*cylinder;
	t_settings	settings;
} t_scene;

t_scene *get_scene(void);
void	init_scene(void);
int	render(const char * input);

    #endif /* MINI_RT_H */
