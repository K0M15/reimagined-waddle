/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:15:54 by kzarins           #+#    #+#             */
/*   Updated: 2025/11/03 22:16:00 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elements.h"
#include "libft.h"
#include "miniRT.h"
#include "parser.h"
#include <errno.h>
#include <stdio.h>

static int	add_light(t_obj *light, t_app *app)
{
	light->mat.color = light->props.color;
	light->mat.is_emitting = 1;
	light->type = POINT_LIGHT;
	return (dyn_add(&app->hitable, light));
}

int	extract_light(const char *line, t_app *app)
{
	char	**tokens;
	t_obj	light;
	double	brightness;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (printf("Could not split the tokens or malloc failed!\n"), -1);
	if (token_ammount(tokens) != 4)
		return (free_tokens(tokens), -1);
	if (ft_strncmp(tokens[0], "L", 10) != 0)
		return (free_tokens(tokens), -1);
	errno = 0;
	light.props.position = extract_loc(tokens[1]);
	if (errno)
		return (free_tokens(tokens), -1);
	light.props.brightness = ft_atof(tokens[2]);
	brightness = light.props.brightness;
	if (errno || brightness > (double)1.0 || brightness < (double)0.0)
		return (free_tokens(tokens), -1);
	light.props.color = extract_color(tokens[3]);
	if (errno)
		return (free_tokens(tokens), -1);
	if (add_light(&light, app))
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}
