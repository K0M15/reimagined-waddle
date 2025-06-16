/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:43:59 by afelger           #+#    #+#             */
/*   Updated: 2025/06/16 20:14:30 by afelger          ###   ########.fr       */
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
    SPHERE,
    CYLINDER,
    PLANE,
    ERROR = 0xFFFF
};

typedef struct s_obj
{
    enum e_obj_type type;
    t_vec3          color;
    void            *props;
    double          reflectivity;
}   t_obj;

typedef struct s_sphere_p{
    float radius;
    t_vec3 position;
}   t_sphere_p;

typedef struct s_cylinder_p{
    float radius;
    float height;
    t_vec3 position;
    t_vec3 rotation;
}   t_cylinder_p;

typedef struct s_plane_p{
    t_vec3  position;
    t_vec3  rotation;
}   t_plane_p;


typedef struct s_hitrec
{
    t_obj   *obj;
    t_vec3 hit;
    t_vec3 normal;
    double t;
    bool front_face;
}   t_hitrec;

t_obj ft_sphere_create(t_sphere_p params, t_vec3 color, float reflectivity);
uint32_t ft_sphere_hit(t_obj sphere, t_ray ray, double min, double max, t_hitrec *rec);
t_obj   ft_cylinder_create(t_cylinder_p params, t_vec3 color);
t_obj   ft_plane_create(t_plane_p params, t_vec3 color);
void ft_obj_dest(t_obj sphere);

void ft_cylinder_assign(t_obj *cylinder, float r, float l, t_vec3 pos, t_vec3 rot)
{
    ((float *)cylinder->props)[0] = r;
    memcpy(&((float *)cylinder->props)[1], &pos, sizeof(t_vec3));
    ((float *)cylinder->props)[4] = l;
    memcpy(&((float *)cylinder->props)[5], &rot, sizeof(t_vec3));
}
// craete a a cylinder prop struct
t_obj ft_cylinder_create(float radius, float length, t_vec3 position, t_vec3 rotation)
{
    t_obj   cyl;

    cyl.type = CYLINDER;
    cyl.props = malloc(sizeof(float)*2 + sizeof(t_vec3)*2);
    ft_cylinder_assign(&cyl, radius, length, position, rotation);
    return cyl;
}

t_obj ft_cylinder_getprops()

#endif /* FT_HITABLE_H */
