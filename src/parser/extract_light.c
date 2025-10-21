#include <errno.h>
#include <stdio.h>
#include "minirt.h"
#include "libft.h"
#include "settings.h"
#include "elements.h"
#include "parser.h"
#include "ft_ll.h"

static int	add_light(t_vec3 *loc, FLOAT *brightness, t_vec3 *color, t_app *app)
{
	t_obj	light;

	light.props.brightness = *brightness;
	cpy_loc(&(light.props.position), loc);
	cpy_rgb(&light.props.color, color);
	light.type = POINT_LIGHT;
	light.mat = NULL;
	return (dyn_add(&app->hitable, &light));
}

int	extract_light(const char *line, t_app *app)
{
	char	**tokens;
	t_vec3	loc;
	FLOAT	brightness;
	t_vec3	color;

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
	if (add_light(&loc, &brightness, &color, app))
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}
