/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:48:48 by kzarins           #+#    #+#             */
/*   Updated: 2025/11/05 13:12:22 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include "parser.h"

void	ft_kumul_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
	uint8_t	*pixel;

	pixel = &image->pixels[(y * image->width + x) * 4];
	*(pixel) = ((uint8_t)(color >> 24) + *pixel) / 2;
	pixel++;
	*(pixel) = ((uint8_t)(color >> 16) + *pixel) / 2;
	pixel++;
	*(pixel) = ((uint8_t)(color >> 8) + *pixel) / 2;
	pixel++;
	*(pixel) = ((uint8_t)(color & 0xFF) + *pixel) / 2;
}

void	ft_put_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
	uint8_t	*pixel;

	pixel = &image->pixels[(y * image->width + x) * 4];
	*(pixel) = (uint8_t)(color >> 24);
	pixel++;
	*(pixel) = (uint8_t)(color >> 16);
	pixel++;
	*(pixel) = (uint8_t)(color >> 8);
	pixel++;
	*(pixel) = (uint8_t)(color & 0xFF);
}
