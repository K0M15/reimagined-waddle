/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:27:34 by afelger           #+#    #+#             */
/*   Updated: 2025/11/03 13:42:22 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include "miniRT.h"
#include "libft.h"
#include "elements.h"
#include "parser.h"

static int	add_cone(t_props *input, t_app *app)
{
	t_obj	cone;

	cone.props.radius = input->radius;
	cone.props.height = input->height;
	cpy_loc(&(cone.props.position), &input->position);
	cpy_rgb(&cone.props.color, &input->color);
	cpy_normal(&cone.props.rotation, &input->rotation);
	cone.type = CONE;
	return (dyn_add(&app->hitable, &cone));
}

int	extract_cone(const char *line, t_app *app)
{
	char		**tokens;
	t_props		temp;

	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed!\n");
		return (-1);
	}
	if (token_ammount(tokens) != 6)
		return (free_tokens(tokens), -1);
	if (ft_strncmp(tokens[0], "co", 10) != 0)
		return (free_tokens(tokens), -1);
	errno = 0;
	temp.position = extract_loc(tokens[1]);
	if (errno)
		return (free_tokens(tokens), -1);
	temp.rotation = extract_normal(tokens[2]);
	if (errno)
		return (free_tokens(tokens), -1);
	temp.radius = atof(tokens[3]) / 2;
	if (errno || temp.diameter <= (double)0)
		return (free_tokens(tokens), -1);
	temp.height = atof(tokens[4]);
	if (errno || temp.height <= (double)0)
		return (free_tokens(tokens), -1);
	temp.color = extract_color(tokens[5]);
	if (errno)
		return (free_tokens(tokens), -1);
	if (add_cone(&temp, app))
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}
