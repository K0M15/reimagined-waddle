#include <errno.h>
#include <stdio.h>
#include "miniRT.h"
#include "libft.h"
#include "elements.h"
#include "parser.h"
#include "hitable.h"

/*TODO: have the possibility to add more materials to the sphere*/
//static int	add_sphere(t_vec3 *loc, double *diameter, t_vec3 *color, t_app *app)
static int	add_sphere(t_obj *sphere, t_app *app)
{
	//t_obj	sphere;

	//sphere.props.radius = *diameter / 2.0;
	//cpy_loc(&(sphere.props.position), loc);
	//cpy_rgb(&sphere.props.color, color);
	//sphere.type = SPHERE;
	return (dyn_add(&app->hitable, sphere));
}

int	extract_sphere(const char *line, t_app *app)
{
	char	**tokens;
//	t_vec3	loc;
//	double	diameter;
//	t_vec3	color;
	t_obj	sphere;

	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed!\n");
		return (-1);
	}
	if (token_ammount(tokens) != 4 || token_ammount(tokens) != 9)
		return (free_tokens(tokens), -1);
	if (ft_strncmp(tokens[0], "sp", 10) != 0)
		return (free_tokens(tokens), -1);
	errno = 0;
	init_material(&sphere);
	sphere.props.position = extract_loc(tokens[1]);
	if (errno)
		return (free_tokens(tokens), -1);
	sphere.props.radius = ft_atof(tokens[2])/2;
	if (errno)
		return (free_tokens(tokens), -1);
	if (sphere.props.radius <= (double)0.0)
		return (free_tokens(tokens), -1);
	sphere.props.color = extract_color(tokens[3]);
	if (errno)
		return (free_tokens(tokens), -1);
	if (token_ammount(tokens) == 9 && pars_bonus_tokens(3, tokens, &sphere) == -1)
		return (free_tokens(tokens), -1);
	if (add_sphere(&sphere, app))
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}
