/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <afelger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:11:42 by afelger           #+#    #+#             */
/*   Updated: 2025/10/29 19:14:02 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "hitable.h"

t_vec3	tex_sample(const mlx_texture_t *tex, t_uv uv, uint32_t *checkerboard)
{
	uint32_t	pos[2];
	uint32_t	id;
	uint8_t		*px;

	if (!tex)
	{
		if ((int)(uv.u * 10.0f) % 2 == (int)(uv.v * 10.0f) % 2)
			return (*checkerboard = true, ftvec3(0));
		else
			return (*checkerboard = true, ftvec3(1));
	}
	*checkerboard = false;
	pos[0] = (uint32_t)fmodf(floorf(uv.u * tex->width), (float)tex->width);
	pos[1] = (uint32_t)fmodf(floorf((1.f - uv.v)
				* tex->height), (float)tex->height);
	id = pos[1] * tex->width + pos[0];
	if (id > tex->width * tex->height)
		id = 0;
	px = tex->pixels + id * tex->bytes_per_pixel;
	return ((t_vec3){px[0] / 255.0f, px[1] / 255.0f, px[2] / 255.0f});
}
