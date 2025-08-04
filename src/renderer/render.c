#include <stdlib.h>
#include "minirt.h"
#include "settings.h"
#include "parser.h"

#include <stdio.h>
int	render(const char * input)
{
	int	x;
	int	y;
	t_point	pixel;

	x = 0;
	y = 0;
	init_scene();
	if (pars(input))
	{
	//TODO:Implement freeing of the scene
	//	free_scene();
		return (-1);
	}
	while (y < IMAGE_HEIGHT)
	{
		while (x < IMAGE_WIDTH)
		{
		//TODO: Implement some operations
			(void)pixel;
			x++;
		}
		x = 0;
		y++;
	}
	//	free_scene();
	return (0);
}
