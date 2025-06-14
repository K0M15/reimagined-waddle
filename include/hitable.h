/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:43:59 by afelger           #+#    #+#             */
/*   Updated: 2025/06/14 17:06:32 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HITABLE_H
# define FT_HITABLE_H

# include <stdint.h>
# include <stdlib.h>
# include "ftray.h"
# include "ftvec3.h"
# include "dyn_arr.h"

enum e_obj_type{
    SPHERE
};

typedef struct s_obj
{
    enum e_obj_type type;
    void           *props;
}   t_obj;

typedef struct s_hitrec
{
    t_vec3 hit;
    t_vec3 normal;
    double t;
}   t_hitrec;

void ft_sphere_assign(t_obj *sphere, float radius, t_vec3 position)
{
    float *sphere_r;
    t_vec3 *sphere_pos;

    sphere_r = sphere->props;
    sphere_pos = sphere->props + sizeof(float);
    *sphere_r = radius;
    sphere_pos->x = position.x;
    sphere_pos->y = position.y;
    sphere_pos->z = position.z;
}

t_obj ft_sphere_create(float radius, t_vec3 position)
{
    t_obj sphere;

    sphere.type = SPHERE;
    sphere.props = malloc(sizeof(float) + sizeof(t_vec3));
    ft_sphere_assign(&sphere, fmax(radius, 0.0), position);
    return sphere;
}

t_vec3 ft_sphere_getcenter(void *props)
{
    return *(t_vec3 *)(props + sizeof(float));
}

float ft_sphere_getradius(void *props)
{
    return *(float *)props;
}

uint32_t ft_sphere_hit(t_obj sphere, t_ray ray, double min, double max, t_hitrec *rec)
{
    t_vec3 oc;
    t_vec3 abc;
    float disciminant;
    float root;

    oc = ftvec3_minus(ft_sphere_getcenter(sphere.props), ray.origin);
    abc = (t_vec3) {
        ftvec3_dot(ray.direction, ray.direction),
        ftvec3_dot(ray.direction, oc),
        ftvec3_dot(oc, oc) - frexpf(ft_sphere_getradius(sphere.props), 2.0)
    };
    disciminant = (abc.y*abc.y - abc.x * abc.z);
    if (disciminant < 0)
        return 0;
    disciminant = sqrtf(disciminant);
    root = (abc.y - disciminant) / abc.x;
    if (root <= min || max <= root)
    {
        root = (abc.y + disciminant) / abc.x;
        if (root <= min || max <= root)
            return false;
    }
    rec->t = root;
    rec->hit = ftray_at(ray, root);
    rec->normal = ftvec3_divide(ftvec3_minus(rec->hit, ft_sphere_getcenter(sphere.props)), FTVEC3(ft_sphere_getradius(sphere.props)));
    return true;
}

void ft_sphere_dest(t_obj sphere)
{
    free(sphere.props);
}

#endif /* FT_HITABLE_H */