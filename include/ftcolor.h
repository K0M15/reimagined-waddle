/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftcolor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:58:31 by afelger           #+#    #+#             */
/*   Updated: 2025/10/13 14:09:05 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftvec3.h"

t_vec3	ftcol_scale(t_vec3 color, float scale);
/*
	Adding the light would be needed with adding to color light sources,
	or adding diffuse and specular reflections
*/
t_vec3	ftcol_add(t_vec3 c1, t_vec3 c2);
/*
	Multipling colors for filtering = reflections
*/
t_vec3	ftcol_mult(t_vec3 c1, t_vec3 c2);

