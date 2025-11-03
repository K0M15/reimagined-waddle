/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:53:17 by kzarins           #+#    #+#             */
/*   Updated: 2025/11/03 21:53:26 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elements.h"
#include "hitable.h"
#include "libft.h"
#include "miniRT.h"
#include "parser.h"
#include <errno.h>
#include <stdio.h>

static int	add_sphere(t_obj *sphere, t_app *app)
{
	sphere->type = SPHERE;
	sphere->mat.color = sphere->props.color;
	return (dyn_add(&app->hitable, sphere));
}

static int	extract_default_props(t_obj *sphere, char **tokens)
{
	sphere->props.position = extract_loc(tokens[1]);
	if (errno)
		return (free_tokens(tokens), -1);
	sphere->props.radius = ft_atof(tokens[2]) / 2;
	if (errno)
		return (free_tokens(tokens), -1);
	if (sphere->props.radius <= (double)0.0)
		return (free_tokens(tokens), -1);
	sphere->props.color = extract_color(tokens[3]);
	if (errno)
		return (free_tokens(tokens), -1);
	return (0);
}

int	extract_sphere(const char *line, t_app *app)
{
	char	**tokens;
	t_obj	sphere;

	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed!\n");
		return (-1);
	}
	if (token_ammount(tokens) != 4 && token_ammount(tokens) != 10)
		return (free_tokens(tokens), -1);
	if (ft_strncmp(tokens[0], "sp", 10) != 0)
		return (free_tokens(tokens), -1);
	errno = 0;
	init_material(&sphere);
	if (extract_default_props(&sphere, tokens) == -1)
		return (-1);
	if (token_ammount(tokens) == 10
		&& pars_bonus_tokens(3, tokens, &sphere) == -1)
		return (free_tokens(tokens), -1);
	if (add_sphere(&sphere, app))
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}
