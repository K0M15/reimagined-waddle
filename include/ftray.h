/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftray.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger93+42@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:07:56 by afelger           #+#    #+#             */
/*   Updated: 2025/06/14 15:22:42 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RAY_H
# define FT_RAY_H

#include <stdint.h>
#include "ftvec3.h"

typedef struct s_ray{
    t_vec3 origin;  // The starting point of the ray
    t_vec3 direction; // The direction in which the ray is pointing
}   t_ray;

t_ray ftray_create(t_vec3 origin, t_vec3 direction);
t_vec3 ftray_at(t_ray ray, float t);
uint32_t ftray_color(t_ray ray);

#endif /* FT_RAY_H */
