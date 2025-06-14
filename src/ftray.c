/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftray.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:53:33 by afelger           #+#    #+#             */
/*   Updated: 2025/06/14 17:01:51 by afelger          ###   ########.fr       */
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

uint32_t world_hit(t_dyn *world, t_ray ray, double min, double max, t_hitrec *rec)
{
    t_hitrec temp;
    uint32_t anything = 0;
    double closest = max;
    int ctr = 0;
    while (ctr < world->filled)
    {
        t_obj *obj = world->elem + ctr*world->mem_size;
        uint32_t hit = 0;
        if (obj->type == SPHERE)
            hit = ft_sphere_hit(obj, ray, min, max, &temp);
        if (hit)
        {
            anything = 1;
            closest = temp.t;
            rec->hit = temp.hit;
            rec->normal = temp.normal;
            rec->t = temp.t;
        }
        ctr++;
    }
    return anything;
}

uint32_t ftray_color(t_ray ray, t_dyn *arr)
{
    float a;
    t_vec3 unit_dir;
    t_vec3 color;
    float hit;
    t_hitrec rec;

    if (world_hit(arr, ray, 0, INFINITY, &rec))
        return ftvec3_tocolor(ftvec3_multiply(FTVEC3(0.5), ftvec3_plus(rec.normal, FTVEC3(1))), 1);
    unit_dir = ftvec3_unit(ray.direction);
    a = 0.5 * (unit_dir.y + 1.0);
    color = ftvec3_plus(ftvec3_multiply(FTVEC3(1.0-a), FTVEC3(1.0)), ftvec3_multiply(FTVEC3(a), (t_vec3){0.5, 0.7, 1.0}));
    return ftvec3_tocolor(color, 1.0);
}