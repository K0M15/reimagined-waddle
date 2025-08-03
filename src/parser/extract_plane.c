#include <errno.h>
#include <stdio.h>
#include "minirt.h"
#include "libft.h"
#include "settings.h"
#include "elements.h"
#include "parser.h"
#include "ft_ll.h"

static int	add_plane(t_point *loc, t_normal *normal, t_rgb *color)
{
	t_plane	*plane;
	
	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!plane)
	{
		printf("Malloc failed!\n");
		return (-1);
	}
	cpy_normal(&plane->normal, normal);
	cpy_loc(&plane->loc, loc);
	cpy_rgb(&plane->color, color);
	add_ll_back_node(&(get_scene()->plane), plane);
	return (0);
}

int	extract_plane(const char *line)
{
	char	**tokens;
	t_point		loc;
	t_normal	normal;
	t_rgb		color;

	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed!\n");
		return (-1);
	}
	if (token_ammount(tokens) != 4)
		return (free_tokens(tokens), -1);
	if (ft_strncmp(tokens[0], "pl", 10) != 0)
		return (free_tokens(tokens), -1);
	errno = 0;
	loc = extract_loc(tokens[1]);
	if (errno)
		return (free_tokens(tokens), -1);
	normal = extract_normal(tokens[2]);
	if (errno)
		return (free_tokens(tokens), -1);
	color = extract_color(tokens[3]);
	if (errno)
		return (free_tokens(tokens), -1);
	if (add_plane(&loc, &brightness, &color) == -1)
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}
