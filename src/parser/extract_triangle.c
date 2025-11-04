/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_triangle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:53:05 by afelger           #+#    #+#             */
/*   Updated: 2025/11/04 00:02:33 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <assert.h>
#include "miniRT.h"
#include "libft.h"
#include "elements.h"
#include "parser.h"

static int	extract_default_props(t_obj *tri, char **tokens)
{
	t_vec3	vert3;

	tri->props.position = extract_loc(tokens[1]);
	if (errno)
		return (free_tokens(tokens), -1);
	tri->props.rotation = extract_loc(tokens[2]);
	if (errno)
		return (free_tokens(tokens), -1);
	vert3 = extract_loc(tokens[3]);
	if (errno)
		return (free_tokens(tokens), -1);
	tri->props.radius = vert3.x;
	tri->props.diameter = vert3.y;
	tri->props.height = vert3.z;
	tri->props.color = extract_color(tokens[4]);
	tri->mat.color = tri->props.color;
	tri->type = TRIANGLE;
	return (0);
}

int	extract_triangle(const char *line, t_app *app)
{
	char	**tokens;
	t_obj	tri;

	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed\n");
		return (-1);
	}
	if (token_ammount(tokens) != 5 && token_ammount(tokens) != 11)
		return (free_tokens(tokens), -1);
	if (ft_strncmp(tokens[0], "tr", 2) != 0)
		return (free_tokens(tokens), -1);
	errno = 0;
	init_material(&tri);
	if (extract_default_props(&tri, tokens) == -1)
		return (-1);
	if (token_ammount(tokens) == 11 && pars_bonus_tokens(4, tokens, &tri) == -1)
		return (free_tokens(tokens), -1);
	if (errno || dyn_add(&app->hitable, &tri))
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}
