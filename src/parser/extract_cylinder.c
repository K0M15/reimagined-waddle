#include <errno.h>
#include <stdio.h>
#include "minirt.h"
#include "libft.h"
#include "settings.h"
#include "elements.h"
#include "parser.h"
#include "ft_ll.h"

static int	add_cylinder(t_cylinder *input)
{
	t_cylinder	*cylinder;
	
	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cylinder)
	{
		printf("Malloc failed!\n");
		return (-1);
	}
	cpy_loc(&cylinder->loc, &input->loc);
	cpy_normal(&cylinder->normal, &input->normal);
	cylinder->diameter = input->diameter;
	cylinder->height = input->height;
	//cpy_rgb(&cylinder->color, &input->color);
	add_ll_back_node(&(get_scene()->cylinder), cylinder);
	return (0);
}

int	extract_cylinder(const char *line, t_app *app)
{
	char		**tokens;
	t_cylinder	temp;
	(void) app;

	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed!\n");
		return (-1);
	}
	if (token_ammount(tokens) != 6)
		return (free_tokens(tokens), -1);
	if (ft_strncmp(tokens[0], "cy", 10) != 0)
		return (free_tokens(tokens), -1);
	errno = 0;
	temp.loc = extract_loc(tokens[1]);
	if (errno)
		return (free_tokens(tokens), -1);
	temp.normal = extract_normal(tokens[2]);
	if (errno)
		return (free_tokens(tokens), -1);
	temp.diameter = atof(tokens[3]);
	if (errno || temp.diameter < (FLOAT)0)
		return (free_tokens(tokens), -1);
	temp.height = atof(tokens[4]);
	if (errno || temp.height < (FLOAT)0)
		return (free_tokens(tokens), -1);
	temp.color = extract_color(tokens[5]);
	if (errno)
		return (free_tokens(tokens), -1);
	if (add_cylinder(&temp) == -1)
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}
