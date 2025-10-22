/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftray.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:07:56 by afelger           #+#    #+#             */
/*   Updated: 2025/10/13 14:37:55 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTRAY_H
# define FTRAY_H

# include <stdint.h>
# include "ftvec3.h"
# include "dyn_arr.h"

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	t_vec3	ambient;
	float	ambient_intensity;
}	t_ray;

t_ray	ftray_create(t_vec3 ambient, float ambient_intensity,
			t_vec3 origin, t_vec3 direction);
t_vec3	ftray_at(t_ray ray, float t);

#endif /* FTRAY_H */
