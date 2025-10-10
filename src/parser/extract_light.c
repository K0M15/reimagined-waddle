#include <errno.h>
#include <stdio.h>
#include "minirt.h"
#include "libft.h"
#include "settings.h"
#include "elements.h"
#include "parser.h"
#include "ft_ll.h"

static int	add_light(t_point *loc, FLOAT *brightness, t_rgb *color)
{
	t_light	*light;
	
	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
	{
		printf("Malloc failed!\n");
		return (-1);
	}
	light->brightness = *brightness;
	cpy_loc(&light->loc, loc);
	cpy_rgb(&light->color, color);
	add_ll_back_node(&(get_scene()->light), light);
	return (0);
}

int	extract_light(const char *line)
{
	char	**tokens;
	t_point	loc;
	FLOAT	brightness;
	t_rgb	color;

	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed!\n");
		return (-1);
	}
	if (token_ammount(tokens) != 4)
		return (free_tokens(tokens), -1);
	if (ft_strncmp(tokens[0], "L", 10) != 0)
		return (free_tokens(tokens), -1);
	errno = 0;
	loc = extract_loc(tokens[1]);
	if (errno)
		return (free_tokens(tokens), -1);
	brightness = ft_atof(tokens[2]);
	if (errno)
		return (free_tokens(tokens), -1);
	if (brightness > (FLOAT)1.0 && brightness < (FLOAT)0.0)
		return (free_tokens(tokens), -1);
	color = extract_color(tokens[3]);
	if (errno)
		return (free_tokens(tokens), -1);
	if (add_light(&loc, &brightness, &color) == -1)
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}
