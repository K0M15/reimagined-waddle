#include <errno.h>
#include <stdio.h>
#include "minirt.h"
#include "libft.h"
#include "settings.h"
#include "elements.h"
#include "parser.h"
#include "ft_ll.h"
#include "hitable.h"

/*TODO: have the possibility to add more materials to the sphere*/
static int	add_sphere(t_vec3 *loc, FLOAT *diameter, t_vec3 *color, t_app *app)
{
	t_obj	sphere;

	sphere.props.radius = *diameter / 2.0;
	//sphere->diameter = *diameter;
	cpy_loc(&(sphere.props.position), loc);
	cpy_rgb(&sphere.props.color, color);
	sphere.type = SPHERE;
	sphere.mat = NULL;
	return (dyn_add(&app->hitable, &sphere));
}

int	extract_sphere(const char *line, t_app *app)
{
	char	**tokens;
	t_vec3	loc;
	FLOAT	diameter;
	t_vec3	color;

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
	if (add_sphere(&loc, &diameter, &color, app))
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}
