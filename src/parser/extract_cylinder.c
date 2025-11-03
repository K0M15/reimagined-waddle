/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:36:29 by kzarins           #+#    #+#             */
/*   Updated: 2025/11/03 22:42:31 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elements.h"
#include "libft.h"
#include "miniRT.h"
#include "parser.h"
#include <errno.h>
#include <stdio.h>

static int	add_cylinder(t_obj *input, t_app *app)
{
	input->type = CYLINDER;
	input->mat.color = input->props.color;
	return (dyn_add(&app->hitable, input));
}

static int	extract_default_props(t_obj *cyl, char **tokens)
{
	cyl->props.position = extract_loc(tokens[1]);
	if (errno)
		return (free_tokens(tokens), -1);
	cyl->props.rotation = extract_normal(tokens[2]);
	if (errno)
		return (free_tokens(tokens), -1);
	cyl->props.radius = atof(tokens[3]) / 2.0;
	if (errno || cyl->props.radius <= (double)0)
		return (free_tokens(tokens), -1);
	cyl->props.height = atof(tokens[4]);
	if (errno || cyl->props.height <= (double)0)
		return (free_tokens(tokens), -1);
	cyl->props.color = extract_color(tokens[5]);
	if (errno)
		return (free_tokens(tokens), -1);
	return (0);
}

int	extract_cylinder(const char *line, t_app *app)
{
	char	**tokens;
	t_obj	cyl;

	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed!\n");
		return (-1);
	}
	if (token_ammount(tokens) != 6 && token_ammount(tokens) != 12)
		return (free_tokens(tokens), -1);
	if (ft_strncmp(tokens[0], "cy", 10) != 0)
		return (free_tokens(tokens), -1);
	errno = 0;
	init_material(&cyl);
	extract_default_props(&cyl, tokens);
	if (token_ammount(tokens) == 12 && pars_bonus_tokens(5, tokens, &cyl) == -1)
		return (free_tokens(tokens), -1);
	if (add_cylinder(&cyl, app))
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}
