/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftray.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:53:33 by afelger           #+#    #+#             */
/*   Updated: 2025/06/14 15:30:54 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftray.h"

t_ray ftray_create(t_vec3 origin, t_vec3 direction)
{
    t_ray ray;

    ray.origin = origin;
    ray.direction = direction;

    return ray;
}

t_vec3 ftray_at(t_ray ray, float t)
{
    return ftvec3_plus(ray.origin, ftvec3_multiply(ray.direction, (t_vec3){t, t, t}));
}

double ftray_hit_sphere(t_vec3 center, float radius, t_ray ray)
{
    t_vec3 oc;
    t_vec3 abc;
    float disciminant;
    oc = ftvec3_minus(center, ray.origin);
    abc = (t_vec3) {
        ftvec3_dot(ray.direction, ray.direction),
        ftvec3_dot(ray.direction, oc),
        ftvec3_dot(oc, oc) - radius * radius
    };
    disciminant = (abc.y*abc.y - abc.x * abc.z);
    if (disciminant < 0)
        return -1.0;
    return abc.y - sqrtf(disciminant) / abc.x;
}

uint32_t ftray_color(t_ray ray)
{
    float a;
    t_vec3 unit_dir;
    t_vec3 color;
    float hit;

    hit = ftray_hit_sphere((t_vec3){0,0,-2}, .5, ray);
    if (hit > 0.0) {
        color = ftvec3_unit(ftvec3_minus(ftray_at(ray, hit), (t_vec3){0,0,-2}));
        return ftvec3_tocolor(ftvec3_multiply(ftvec3_plus(color, FTVEC3(1)), (t_vec3){0.5, 1, 1}), 1.0);
    }
    unit_dir = ftvec3_unit(ray.direction);
    a = 0.5 * (unit_dir.y + 1.0);
    color = ftvec3_plus(ftvec3_multiply(FTVEC3(1.0-a), FTVEC3(1.0)), ftvec3_multiply(FTVEC3(a), (t_vec3){0.5, 0.7, 1.0}));
    return ftvec3_tocolor(color, 1.0);
}