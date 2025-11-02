/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_triangle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afelger <alain.felger@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:53:05 by afelger           #+#    #+#             */
/*   Updated: 2025/11/01 17:53:24 by afelger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <assert.h>
#include "miniRT.h"
#include "libft.h"
#include "elements.h"
#include "parser.h"


int	extract_triangle(const char *line, t_app *app)
{
    char	**tokens;
	t_obj	temp;
	t_vec3	vert3;

	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed\n");
		return (-1);
	}
	if (token_ammount(tokens) != 5)
		return (free_tokens(tokens), -1);
	if (ft_strncmp(tokens[0], "tr", 2) != 0)
		return (free_tokens(tokens), -1);
	errno = 0;
	temp.props.position = extract_loc(tokens[1]);
	if (errno)
		return (free_tokens(tokens), -1);
	temp.props.rotation = extract_loc(tokens[2]);
	if (errno)
		return (free_tokens(tokens), -1);
	vert3 = extract_loc(tokens[3]);
	if (errno)
		return (free_tokens(tokens), -1);
	temp.props.radius = vert3.x;
	temp.props.diameter = vert3.y;
	temp.props.height = vert3.z;
	temp.props.color = extract_color(tokens[4]);
	temp.type = TRIANGLE;
	if (errno || dyn_add(&app->hitable, &temp))
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}