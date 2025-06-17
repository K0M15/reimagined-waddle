/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftray.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:53:33 by afelger           #+#    #+#             */
/*   Updated: 2025/06/17 18:54:01 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftray.h"

t_ray ftray_create(t_vec3 ambient, t_vec3 origin, t_vec3 direction)
{
    t_ray ray;

    ray.origin = origin;
    ray.direction = direction;
    ray.ambient = ambient;

    return ray;
}

t_vec3 ftray_at(t_ray ray, float t)
{
    return ftvec3_plus(ray.origin, ftvec3_multiply(ray.direction, (t_vec3){t, t, t}));
}
