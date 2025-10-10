/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:43:59 by afelger           #+#    #+#             */
/*   Updated: 2025/09/05 15:32:41 by afelger          ###   ########.fr       */
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

typedef struct s_material
{
    double  reflectivity;
    double  scatter;
    t_vec3          color;
    bool    is_emitting;
}   t_material;

typedef struct s_obj
{
    enum e_obj_type type;
    void            *props;
    t_material      *mat;   //Maybe change object to have 
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
    t_vec3 hit;
    t_vec3 normal;
    t_material  *mat;
    double t;
    bool front_face;
}   t_hitrec;

t_obj ft_sphere_create(t_sphere_p params, t_material *mat);
uint32_t ft_sphere_hit(t_obj sphere, t_ray ray, double min, double max, t_hitrec *rec);
t_obj   ft_cylinder_create(t_cylinder_p params, t_material *mat);
t_obj   ft_plane_create(t_plane_p params, t_material *mat);
void ft_obj_dest(t_obj sphere);

#endif /* FT_HITABLE_H */
