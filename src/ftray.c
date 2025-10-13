/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftray.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:53:33 by afelger           #+#    #+#             */
/*   Updated: 2025/10/11 11:04:44 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftray.h"

t_ray	ftray_create(t_vec3 ambient, float ambient_intensity, t_vec3 origin,
	t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	ray.ambient = ambient;
	ray.ambient_intensity = ambient_intensity;
	return (ray);
}

t_vec3	ftray_at(t_ray ray, float t)
{
	return (ftvec3_plus(ray.origin, ftvec3_multiply(
				ray.direction, (t_vec3){t, t, t})));
}
