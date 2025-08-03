#include <errno.h>
#include <stdio.h>
#include "minirt.h"
#include "libft.h"
#include "settings.h"
#include "elements.h"
#include "parser.h"
#include "ft_ll.h"

static int	add_sphere(t_point *loc, FLOAT *diameter, t_rgb *color)
{
	t_sphere	*sphere;
	
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
	{
		printf("Malloc failed!\n");
		return (-1);
	}
	sphere->diameter = *diameter;
	cpy_loc(&sphere->loc, loc);
	cpy_rgb(&sphere->color, color);
	add_ll_back_node(&(get_scene()->sphere), sphere);
	return (0);
}

int	extract_sphere(const char *line)
{
	char	**tokens;
	t_point	loc;
	FLOAT	diameter;
	t_rgb	color;

	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed!\n");
		return (-1);
	}
	if (token_ammount(tokens) != 4)
		return (free_tokens(tokens), -1);
	if (ft_strncmp(tokens[0], "sp", 10) != 0)
		return (free_tokens(tokens), -1);
	errno = 0;
	loc = extract_loc(tokens[1]);
	if (errno)
		return (free_tokens(tokens), -1);
	diameter = ft_atof(tokens[2]);
	if (errno)
		return (free_tokens(tokens), -1);
	if (diameter < (FLOAT)0.0)
		return (free_tokens(tokens), -1);
	color = extract_color(tokens[3]);
	if (errno)
		return (free_tokens(tokens), -1);
	if (add_sphere(&loc, &diameter, &color) == -1)
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}
