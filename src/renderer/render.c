#include <stdlib.h>
#include "minirt.h"
#include "settings.h"
#include "parser.h"

#include <stdio.h>
int	render(const char * input)
{
	init_scene();
	if (pars(input))
	{
	//TODO:Implement freeing of the scene
	//	free_scene();
		return (-1);
	}
	return (0);
}
