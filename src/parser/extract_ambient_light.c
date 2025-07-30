#include <errno.h>
#include "minirt.h"
#include "libft.h"
#include "settings.h"
#include "elements.h"

static int	add_ambient_light(FLOAT *light_ratio, t_rgb *color)
{
	t_ambient_light	*a_light;
	
	a_light = (t_ambient_light *)malloc(sizeof(t_ambient_light));
	if (!a_light)
	{
		printf("Malloc failed!\n");
		return (-1);
	}
	a_light->light_ratio = *light_ratio;
	cpy_rgb(a_light, color);
	return (0);
}

//TODO: FT_SPLIT should also have a free function!!!!!
int	extract_ambient_light(const char *line)
{
	char	**tokens;
	FLOAT	light_ratio;
	t_rgb	color;

	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed!\n");
		return (-1);
	}
	if (tokens[3])
		return (-1);
	if (ft_strncmp(tokens[0], 'A', 10) != 0)
		return (-1);
	//TODO: Have to implement atof!!
	errno = 0;
	light_ratio = atof(tokens[1]);
	if (errno)
		return (-1);
	if (light_ratio > (FLOAT)1.0 && light_ratio < (FLOAT)0.0)
		return (-1);
	//TODO: Implement extract_color function
	color = extract_color(tokens[2]);
	if (errno)
		return (-1);
	if (add_ambient_light(&light_ratio, &color) == -1)
		return (-1);
}
