/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:02:57 by kzarins           #+#    #+#             */
/*   Updated: 2025/11/03 22:38:59 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elements.h"
#include "libft.h"
#include "miniRT.h"
#include "parser.h"
#include <errno.h>
#include <stdio.h>

static int	add_plane(t_obj *plane, t_app *app)
{
	plane->type = PLANE;
	plane->mat.color = plane->props.color;
	return (dyn_add(&app->hitable, plane));
}

static int	extract_default_props(t_obj *plane, char **tokens)
{
	errno = 0;
	plane->props.position = extract_loc(tokens[1]);
	if (errno)
		return (free_tokens(tokens), -1);
	plane->props.rotation = extract_normal(tokens[2]);
	if (errno)
		return (free_tokens(tokens), -1);
	plane->props.color = extract_color(tokens[3]);
	if (errno)
		return (free_tokens(tokens), -1);
	return (0);
}

int	extract_plane(const char *line, t_app *app)
{
	char	**tokens;
	t_obj	plane;

	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed!\n");
		return (-1);
	}
	if (token_ammount(tokens) != 4 && token_ammount(tokens) != 10)
		return (free_tokens(tokens), -1);
	if (ft_strncmp(tokens[0], "pl", 10) != 0)
		return (free_tokens(tokens), -1);
	init_material(&plane);
	if (extract_default_props(&plane, tokens) == -1)
		return (-1);
	if (token_ammount(tokens) == 10
		&& pars_bonus_tokens(3, tokens, &plane) == -1)
		return (free_tokens(tokens), -1);
	if (add_plane(&plane, app))
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}
