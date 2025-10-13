#include <errno.h>
#include <stdio.h>
#include "minirt.h"
#include "libft.h"
#include "settings.h"
#include "elements.h"
#include "parser.h"
#include "ft_ll.h"

//TODO: change the t_camera_o to more meaningfull name
//TODO: Add the direct addition to app object
int	add_camera(t_vec3 *loc, t_vec3 *normal, int *fov, t_app *app)
{
	t_camera_o	*a_camera;
	
	(void) app;
	a_camera = (t_camera_o *)malloc(sizeof(t_camera));
	if (!a_camera)
	{
		printf("Malloc failed!\n");
		return (-1);
	}
	a_camera->fov = *fov;
	cpy_loc(&a_camera->loc, loc);
	cpy_normal(&a_camera->normal, normal);
	add_ll_back_node(&(get_scene()->camera), a_camera);
	return (0);
}

static int	extract_fov(char *input)
{
	char	*temp;
	int	len;
	
	temp = input;
	len = 0;
	while (*temp)
	{
		len++;
		if (!ft_isdigit(*temp) || len > 3)
			return (-1);
		temp++;
	}
	return (ft_atoi(input));
}

int	extract_camera(const char *line, t_app *app)
{
	char		**tokens;
	t_vec3		loc;
	t_vec3	normal;
	int		fov;

	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed!\n");
		return (-1);
	}
	if (token_ammount(tokens) != 4)
		return (free_tokens(tokens), -1);
	if (ft_strncmp(tokens[0], "C", 10) != 0)
		return (free_tokens(tokens), -1);
	errno = 0;
	loc = extract_loc(tokens[1]);
	if (errno)
		return (free_tokens(tokens), -1);
	normal = extract_normal(tokens[2]);
	fov = extract_fov(tokens[3]);
	if (fov == -1)
		return (free_tokens(tokens), -1);
	if (fov > (int)180 && fov < (int)0)
		return (free_tokens(tokens), -1);
	if (add_camera(&loc, &normal, &fov, app) == -1)
		return (free_tokens(tokens), -1);
	return (free_tokens(tokens), 0);
}
