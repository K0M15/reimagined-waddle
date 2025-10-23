#include <errno.h>
#include <stdio.h>
#include "minirt.h"
#include "libft.h"
#include "settings.h"
#include "elements.h"
#include "parser.h"
#include "ft_ll.h"

static int	add_ambient_light(FLOAT *light_ratio, t_vec3 *color, t_app *app)
{
	t_ambient_light	*a_light;
	
	(void) app;
	a_light = (t_ambient_light *)malloc(sizeof(t_ambient_light));
	if (!a_light)
	{
		printf("Malloc failed!\n");
		return (-1);
	}
	a_light->lighting_ratio = *light_ratio;
	cpy_rgb(&a_light->color, color);
	add_ll_back_node(&(get_scene()->ambient_light), a_light);
	return (0);
}

int	extract_ambient_light(const char *line, t_app *app)
{
	char	**tokens;
	FLOAT	light_ratio;
	t_vec3	color;

	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed!\n");
		return (-1);
	}
	if (token_ammount(tokens) != 3)
		return (free_tokens(tokens), -1);
	if (ft_strncmp(tokens[0], "A", 10) != 0)
		return (free_tokens(tokens), -1);
	errno = 0;
	light_ratio = ft_atof(tokens[1]);
	if (errno)
		return (free_tokens(tokens), -1);
	if (light_ratio > (FLOAT)1.0 && light_ratio < (FLOAT)0.0)
		return (free_tokens(tokens), -1);
	color = extract_color(tokens[2]);
	if (errno)
		return (free_tokens(tokens), -1);
	if (add_ambient_light(&light_ratio, &color, app) == -1)
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}
