#include <errno.h>
#include <stdio.h>
#include "miniRT.h"
#include "libft.h"
#include "elements.h"
#include "parser.h"

static int	add_cylinder(t_obj *input, t_app *app)
{
	input->type = CYLINDER;
	return (dyn_add(&app->hitable, input));
}

int	extract_cylinder(const char *line, t_app *app)
{
	char		**tokens;
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
	cyl.props.position = extract_loc(tokens[1]);
	if (errno)
		return (free_tokens(tokens), -1);
	cyl.props.rotation = extract_normal(tokens[2]);
	if (errno)
		return (free_tokens(tokens), -1);
	cyl.props.radius = atof(tokens[3]) / 2.0;
	if (errno || cyl.props.diameter <= (double)0)
		return (free_tokens(tokens), -1);
	cyl.props.height = atof(tokens[4]);
	if (errno || cyl.props.height <= (double)0)
		return (free_tokens(tokens), -1);
	cyl.mat.color = extract_color(tokens[5]);
	if (errno)
		return (free_tokens(tokens), -1);
	if (token_ammount(tokens) == 12 && pars_bonus_tokens(5, tokens, &cyl) == -1)
		return (free_tokens(tokens), -1);
	if (add_cylinder(&cyl, app))
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}
