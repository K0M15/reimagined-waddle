/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:11:42 by afelger           #+#    #+#             */
/*   Updated: 2025/11/01 15:02:52 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "hitable.h"

//The old calculation:
//if ((int)(uv.u * 10.0f) % 2 == (int)(uv.v * 10.0f) % 2)
t_vec3	tex_sample(const mlx_texture_t *tex, t_uv uv, uint32_t *checkerboard)
{
	uint32_t	pos[2];
	uint32_t	id;
	uint8_t		*px;

	if (!tex)
	{
		if ((((int)floorf((fmodf((uv.u), 1.f)) * 10.f)
					+ (int)floorf((fmodf((uv.v), 1.f)) * 10.f)) & 1) == 0)
			return (*checkerboard = true, ftvec3(0));
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
