/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:48:48 by kzarins           #+#    #+#             */
/*   Updated: 2025/11/04 20:55:46 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include "parser.h"

void	print_vec3(t_vec3 *vec)
{
	printf("%f,%f,%f", vec->x, vec->y, vec->z);
}

static void	print_instructions(void)
{
	printf("The program usage: ./miniRT [scene file]\n");
}

void ft_kumul_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
	uint8_t *pixel;

	pixel = &image->pixels[(y * image->width + x) * 4];
	*(pixel) = ((uint8_t)(color >> 24) + *pixel) / 2;
	pixel++;
	*(pixel) = ((uint8_t)(color >> 16) + *pixel) / 2;
	pixel++;
	*(pixel) = ((uint8_t)(color >> 8) + *pixel) / 2;
	pixel++;
	*(pixel) = ((uint8_t)(color & 0xFF) + *pixel) / 2;
}

void ft_put_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
	uint8_t *pixel;

	pixel = &image->pixels[(y * image->width + x) * 4];
	*(pixel) = (uint8_t)(color >> 24);
	pixel++;
	*(pixel) = (uint8_t)(color >> 16);
	pixel++;
	*(pixel) = (uint8_t)(color >> 8);
	pixel++;
	*(pixel) = (uint8_t)(color & 0xFF);
}

//TODO: 
void	print_element(int iter, t_app *app)
{
	t_obj		*ptr;
	const char	*types[] = {"SPHERE", "CYLINDER", "PLANE",
        "POINT_LIGHT", "TRIANGLE", "CONE"};
	void	(*func[])(t_obj*)= {print_sphere, print_cylinder,
        print_plane, print_point_light, print_triangle, print_cylinder};

	ptr = app->hitable.elem + iter;
	if (ptr->type == 0xFFFF)
	{
		printf("There is an error type in the objects!!/n");
		return ;
	}
	printf("==========\n");
	printf("The type: %s\n", types[ptr->type]);
	func[ptr->type](ptr);
	printf("\n");
	printf("The materials:\n color: %f, %f, %f; reflectivity: %f;
            is_emitting: %d; scatter: %f", ptr->mat.color.x,\
            ptr->mat.color.y, ptr->mat.color.z, ptr->mat.reflectivity,\
			ptr->mat.is_emitting, ptr->mat.scatter);
	printf("\n==========\n");
}
