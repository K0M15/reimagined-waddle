/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftcamera_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:11:25 by afelger           #+#    #+#             */
/*   Updated: 2025/11/03 19:11:07 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
