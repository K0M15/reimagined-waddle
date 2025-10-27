/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:11:42 by afelger           #+#    #+#             */
/*   Updated: 2025/10/26 10:49:28 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "hitable.h"

t_vec3 tex_sample(const mlx_texture_t *tex, t_uv uv, uint32_t *checkerboard)
{
    if (!tex)
    {
        if ((int)uv.u % 2 == (int)uv.v % 2)
            return (*checkerboard = true, ftvec3(0));
        else
            return (*checkerboard = true, ftvec3(1));
    }
    *checkerboard = false;
    uint32_t w = tex->width, h = tex->height, bpp = tex->bytes_per_pixel;
    uint32_t x = (uint32_t)fmodf(floorf(uv.u * w), (float)w);
    uint32_t y = (uint32_t)fmodf(floorf((1.f - uv.v) * h), (float)h); // flip V
    const uint8_t *px = tex->pixels + (y * w + x) * bpp;
    // MLX42 textures are RGBA8
    return (t_vec3){px[0]/255.0f, px[1]/255.0f, px[3]/255.0f};
    // return (px[3] << 24) | (px[0] << 16) | (px[1] << 8) | (px[2] << 0); // check this!
}

