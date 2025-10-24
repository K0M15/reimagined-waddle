#include <errno.h>
#include <stdio.h>
#include "miniRT.h"
#include "libft.h"
#include "elements.h"
#include "parser.h"

static int	add_cylinder(t_props *input, t_app *app)
{
	t_obj	cylinder;

	cylinder.props.radius = input->diameter / 2.0;
	cylinder.props.height = input->height;
	cpy_loc(&(cylinder.props.position), &input->position);
	cpy_rgb(&cylinder.props.color, &input->color);
	cpy_normal(&cylinder.props.rotation, &input->rotation);
	cylinder.type = CYLINDER;
	return (dyn_add(&app->hitable, &cylinder));
}

int	extract_cylinder(const char *line, t_app *app)
{
	char		**tokens;
	t_props		temp;

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
	temp.position = extract_loc(tokens[1]);
	if (errno)
		return (free_tokens(tokens), -1);
	temp.rotation = extract_normal(tokens[2]);
	if (errno)
		return (free_tokens(tokens), -1);
	temp.diameter = atof(tokens[3]);
	if (errno || temp.diameter < (double)0)
		return (free_tokens(tokens), -1);
	temp.height = atof(tokens[4]);
	if (errno || temp.height < (double)0)
		return (free_tokens(tokens), -1);
	temp.color = extract_color(tokens[5]);
	if (errno)
		return (free_tokens(tokens), -1);
	if (add_cylinder(&temp, app))
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}
