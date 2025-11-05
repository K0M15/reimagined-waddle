/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:11:52 by kzarins           #+#    #+#             */
/*   Updated: 2025/11/05 13:41:20 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include "parser.h"

void	print_vec3(t_vec3 *vec)
{
	printf("%f,%f,%f", vec->x, vec->y, vec->z);
}

void	print_instructions(void)
{
	printf("The program usage: ./miniRT [scene file]\n");
}

void	define_func_ptr(void (*func[6])(t_obj*))
{
	func[0] = print_sphere;
	func[1] = print_cylinder;
	func[2] = print_plane;
	func[3] = print_point_light;
	func[4] = print_triangle;
	func[5] = print_cylinder;
}

void	print_element(int iter, t_app *app)
{
	t_obj		*ptr;
	const char	*types[] = {"SPHERE", "CYLINDER", "PLANE",
		"POINT_LIGHT", "TRIANGLE", "CONE"};
	void		(*func[6])(t_obj*);

	define_func_ptr(func);
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
	printf("The materials:\n color: %f, %f, %f; reflectivity: %f;\
            is_emitting: %d; scatter: %f", ptr->mat.color.x,
		ptr->mat.color.y, ptr->mat.color.z, ptr->mat.reflectivity,
		ptr->mat.is_emitting, ptr->mat.scatter);
	printf("\n==========\n");
}

void	print_internal_data(t_app *app)
{
	uint32_t	iter;

	iter = 0;
	while (iter < app->hitable.filled)
	{
		print_element(iter, app);
		iter++;
	}
	return ;
}
