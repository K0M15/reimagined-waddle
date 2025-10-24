#include <errno.h>
#include <stdio.h>
#include "miniRT.h"
#include "libft.h"
#include "elements.h"
#include "parser.h"

static int	add_plane(t_vec3 *loc, t_vec3 *normal, t_vec3 *color, t_app *app)
{
	t_obj	plane;

	cpy_loc(&(plane.props.position), loc);
	cpy_rgb(&plane.props.color, color);
	cpy_normal(&plane.props.rotation, normal);
	plane.type = PLANE;
	return (dyn_add(&app->hitable, &plane));
}

int	extract_plane(const char *line, t_app *app)
{
	char	**tokens;
	t_vec3		loc;
	t_vec3	normal;
	t_vec3		color;

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
	if (add_plane(&loc, &normal, &color, app))
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}
