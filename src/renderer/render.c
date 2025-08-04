#include <stdlib.h>
#include "minirt.h"
#include "settings.h"
#include "parser.h"

int	render(const char * input)
{
	init_scene();
	if (pars(input))
	{
	//	Implement freeing of the scene
	//	free_scene();
		return (-1);
	}
}
