/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:27:34 by afelger           #+#    #+#             */
/*   Updated: 2025/11/04 00:02:13 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include "miniRT.h"
#include "libft.h"
#include "elements.h"
#include "parser.h"

static int	add_cone(t_obj *cone, t_app *app)
{
	cone->type = CONE;
	cone->mat.color = cone->props.color;
	return (dyn_add(&app->hitable, cone));
}

static int	extract_default_props(t_obj *cone, char **tokens)
{
	cone->props.position = extract_loc(tokens[1]);
	if (errno)
		return (free_tokens(tokens), -1);
	cone->props.rotation = extract_normal(tokens[2]);
	if (errno)
		return (free_tokens(tokens), -1);
	cone->props.radius = atof(tokens[3]) / 2;
	if (errno || cone->props.radius <= (double)0)
		return (free_tokens(tokens), -1);
	cone->props.height = atof(tokens[4]);
	if (errno || cone->props.height <= (double)0)
		return (free_tokens(tokens), -1);
	cone->props.color = extract_color(tokens[5]);
	if (errno)
		return (free_tokens(tokens), -1);
	return (0);
}

int	extract_cone(const char *line, t_app *app)
{
	char		**tokens;
	t_obj		cone;

	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed!\n");
		return (-1);
	}
	if (token_ammount(tokens) != 6 && token_ammount(tokens) != 12)
		return (free_tokens(tokens), -1);
	if (ft_strncmp(tokens[0], "co", 10) != 0)
		return (free_tokens(tokens), -1);
	errno = 0;
	init_material(&cone);
	if (extract_default_props(&cone, tokens) == -1)
		return (-1);
	if (token_ammount(tokens) == 12
		&& pars_bonus_tokens(5, tokens, &cone) == -1)
		return (free_tokens(tokens), -1);
	if (add_cone(&cone, app))
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}
