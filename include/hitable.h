/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:43:59 by afelger           #+#    #+#             */
/*   Updated: 2025/06/15 11:02:53 by afelger          ###   ########.fr       */
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

void ft_sphere_assign(t_obj *sphere, float radius, t_vec3 position);
t_obj ft_sphere_create(float radius, t_vec3 position);
t_vec3 ft_sphere_getcenter(void *props);
float ft_sphere_getradius(void *props);
uint32_t ft_sphere_hit(t_obj sphere, t_ray ray, double min, double max, t_hitrec *rec);
void ft_sphere_dest(t_obj sphere);


#endif /* FT_HITABLE_H */
