/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftvec3_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:02:40 by afelger           #+#    #+#             */
/*   Updated: 2025/10/16 13:10:49 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftvec3.h"

float	ftvec3_length(t_vec3 vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3	ftvec3_normalize(t_vec3 vec)
{
	float	length;
	t_vec3	result;

	length = ftvec3_length(vec);
	if (length != 0)
	{
		result.x = vec.x / length;
		result.y = vec.y / length;
		result.z = vec.z / length;
	}
	else
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
	}
	return (result);
}

t_vec3	ftvec3_unit(t_vec3 v)
{
	float	length;

	length = ftvec3_length(v);
	return (ftvec3_divide(v, (t_vec3){length, length, length}));
}

uint32_t	ftvec3_tocolor(t_vec3 v, float alpha)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;

	r = (uint32_t)(clamp(v.x, 0, 1) * 255.0f);
	g = (uint32_t)(clamp(v.y, 0, 1) * 255.0f);
	b = (uint32_t)(clamp(v.z, 0, 1) * 255.0f);
	a = (uint32_t)(clamp(alpha, 0, 1) * 255.0f);
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

/* Returns a (t_vec3){f,f,f} */
t_vec3	ftvec3(float f)
{
	return ((t_vec3){f, f, f});
}
