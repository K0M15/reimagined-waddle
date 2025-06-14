/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:14:42 by afelger           #+#    #+#             */
/*   Updated: 2025/06/14 16:44:50 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H
# include "MLX42/MLX42.h"
# include "ftray.h"
# include "ftvec3.h"
# include "dyn_arr.h"
# include "hitable.h"
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_camera
{
    t_vec3 center;
    float focal_length;
    float viewport_width;
    float viewport_height;
    t_vec3 u; // Right vector
    t_vec3 v; // Up vector
    t_vec3 delta_u; // Horizontal vector
    t_vec3 delta_v; // Vertical vector
}   t_camera;

typedef struct s_app
{
	mlx_t *mlx;
	mlx_image_t *image;
    int32_t width;
    int32_t height;
    t_camera *active_camera;
    t_dyn   hitable;
}	t_app;


uint32_t ft_camera_init(
    t_camera *camera,
    t_vec3 center,
    float focal_length,
    float viewport_width,
    float viewport_height,
    int imageHeight,
    int imageWidth);

uint32_t ft_camera_render(
    t_camera *camera,
    mlx_image_t *image,
    int32_t (*put_pixel)(mlx_image_t *image, int x, int y, uint32_t color));

#endif /* MINI_RT_H */
