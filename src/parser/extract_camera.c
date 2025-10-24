#include <errno.h>
#include <stdio.h>
#include "miniRT.h"
#include "libft.h"
#include "settings.h"
#include "elements.h"
#include "parser.h"

//TODO: change the t_camera_o to more meaningfull name
//TODO: Add the direct addition to app object
int	add_camera(t_vec3 *loc, t_vec3 *normal, int *fov, t_app *app)
{
	app->active_camera->center = *loc;
	app->active_camera->look_at = *normal;
	app->active_camera->fov = (float)*fov;
	ft_camera_init(app->active_camera, (t_camera_p){
		app->active_camera->center,
		app->active_camera->look_at,
		app->active_camera->fov,
		app->active_camera->image_height,
		app->active_camera->image_width,
		app->active_camera->samples_per_pixel,
		app->active_camera->ambient,
		app->active_camera->ambient_intensity
	});
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
