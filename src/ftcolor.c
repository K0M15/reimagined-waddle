/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftcolor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:50:16 by afelger           #+#    #+#             */
/*   Updated: 2025/10/16 12:47:10 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftcolor.h"

t_vec3	ftcol_scale(t_vec3 color, float scale)
{
	return ((t_vec3){
		color.x * scale,
		color.y * scale,
		color.z * scale
	});
}

t_vec3	ftcol_add(t_vec3 c1, t_vec3 c2)
{
	return (ftvec3_plus(c1, c2));
}

t_vec3	ftcol_mult(t_vec3 c1, t_vec3 c2)
{
	return (ftvec3_multiply(c1, c2));
}
