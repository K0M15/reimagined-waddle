/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 21:11:37 by kzarins           #+#    #+#             */
/*   Updated: 2025/11/03 21:11:37 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elements.h"
#include "libft.h"
#include "miniRT.h"
#include "parser.h"
#include <errno.h>
#include <stdio.h>

int	add_camera(t_app *app)
{
	ft_camera_init(&app->active_camera, (t_camera_p){app->active_camera.center,
		app->active_camera.look_at, app->active_camera.fov, app->width,
		app->height, app->active_camera.samples_per_pixel,
		app->active_camera.ambient, app->active_camera.ambient_intensity, MAX_DEPTH});
	app->active_camera.image_width = app->width;
	app->active_camera.image_height = app->height;
	ft_camera_calc(&app->active_camera);
	return (0);
}

static int	extract_fov(char *input)
{
	char	*temp;
	int		len;

	temp = input;
	len = 0;
	while (*temp)
	{
		len++;
		if (!ft_isdigit(*temp) || len > 3)
			return (-1);
		temp++;
	}
	return (ft_atoi(input));
}

int	extract_camera_prop(char **tokens, t_app *app)
{
	int	fov;

	errno = 0;
	app->active_camera.center = extract_loc(tokens[1]);
	if (errno)
		return (free_tokens(tokens), -1);
	app->active_camera.look_at = extract_normal(tokens[2]);
	if (errno)
		return (free_tokens(tokens), -1);
	app->active_camera.fov = (float)extract_fov(tokens[3]);
	fov = app->active_camera.fov;
	if (fov == -1 || (fov > (int)180 && fov < (int)0))
		return (free_tokens(tokens), -1);
	return (errno);
}

int	extract_camera(const char *line, t_app *app)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed!\n");
		return (-1);
	}
	if (token_ammount(tokens) != 4)
		return (free_tokens(tokens), -1);
	if (ft_strncmp(tokens[0], "C", 10) != 0)
		return (free_tokens(tokens), -1);
	if (extract_camera_prop(tokens, app) == -1)
		return (-1);
	if (add_camera(app) == -1)
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}

void	init_default_camera(t_app *app)
{

	app->width = 120;
	app->height = 80;
	ft_camera_init(
		&app->active_camera, (t_camera_p){
			ftvec3(0),
			(t_vec3){0,0, -1},
			90,
			app->width,
			app->height,
			STAN_SAMPLES_PER_PIXEL,
			(t_vec3){
				1, 1, 1
			},
			.2
			,MAX_DEPTH
		});
	ft_camera_calc(&app->active_camera);
}