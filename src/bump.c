/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:57:14 by afelger           #+#    #+#             */
/*   Updated: 2025/11/01 13:52:28 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hitable.h"

static inline float	luminance(t_vec3 c)
{
	return (c.x + c.y + c.z) * (1.0f / 3.0f);
}

t_uv	interpolate_height(mlx_texture_t *bump, t_uv uv)
{
	t_uv	step;
	float	height[5];

	step.u = 1.0f / (float)bump->width;
	step.v = 1.0f / (float)bump->height;
	height[0] = luminance(tex_sample(bump, (t_uv){uv.u + step.u, uv.v},
				(uint32_t *)&height[4]));
	height[2] = luminance(tex_sample(bump, (t_uv){uv.u - step.u, uv.v},
				(uint32_t *)&height[4]));
	height[1] = luminance(tex_sample(bump, (t_uv){uv.u, uv.v + step.v},
				(uint32_t *)&height[4]));
	height[3] = luminance(tex_sample(bump, (t_uv){uv.u, uv.v - step.v},
				(uint32_t *)&height[4]));
	return ((t_uv){0.5f * (height[0] - height[2]), -(0.5f * (height[1] - height[3]))});
}