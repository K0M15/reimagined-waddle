/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:29:53 by kzarins           #+#    #+#             */
/*   Updated: 2025/11/04 20:49:20 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include "parser.h"

void	print_sphere(t_obj *app)
{
	print_vec3(&app->props.position);
	printf("\t");
	printf("%f", app->props.radius);
	printf("\t");
	print_vec3(&app->props.color);
}

void	print_cylinder(t_obj *app)
{
	print_vec3(&app->props.position);
	printf("\t");
	print_vec3(&app->props.rotation);
	printf("\t");
	printf("%f", app->props.radius);
	printf("\t");
	printf("%f", app->props.height);
	printf("\t");
	print_vec3(&app->props.color);
}

void	print_plane(t_obj *app)
{
	print_vec3(&app->props.position);
	printf("\t");
	print_vec3(&app->props.rotation);
	printf("\t");
	print_vec3(&app->props.color);
}

void	print_point_light(t_obj *app)
{
	print_vec3(&app->props.position);
	printf("\t");
	printf("%f", app->props.brightness);
	printf("\t");
	print_vec3(&app->props.color);
}

void	print_triangle(t_obj *obj)
{
	t_vec3 vert3 = (t_vec3){obj->props.radius, obj->props.diameter, obj->props.height};
	print_vec3(&obj->props.position);
	print_vec3(&obj->props.rotation);
	print_vec3(&vert3);
}