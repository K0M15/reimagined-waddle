#include <stdio.h>
#include <errno.h>
#include "minirt.h"
#include "settings.h"
#include "elements.h"
#include "parser.h"

int	valid_whole_file_test(void)
{
	int	ret;

	ret = 0;
	ret += pars("./tests/maps/example.rt");
	if (ret !=0 )
		return (-1);
	t_node	*temp = get_scene()->ambient_light;
	if (((t_ambient_light *)temp->value)->lighting_ratio != (FLOAT)0.2)
		return (-1);
	if (((t_ambient_light *)temp->value)->color.r != (int)255 || \
	((t_ambient_light *)temp->value)->color.g != (int)255 || \
	((t_ambient_light *)temp->value)->color.b != (int)255)
		return (-1);
	temp = get_scene()->camera;
	if (((t_camera *)temp->value)->loc.x != (FLOAT)-50 || \
	((t_camera *)temp->value)->loc.y != (FLOAT)0 || \
	((t_camera *)temp->value)->loc.z != (FLOAT)20)
		return (-1);
	if (((t_camera *)temp->value)->normal.x != (FLOAT)0 || \
	((t_camera *)temp->value)->normal.y != (FLOAT)0 || \
	((t_camera *)temp->value)->normal.z != (FLOAT)0)
		return (-1);
	if (((t_camera *)temp->value)->fov != (int)70)
		return (-1);
	temp = get_scene()->light;
	if (((t_light *)temp->value)->loc.x != (FLOAT)-40 || \
	((t_light *)temp->value)->loc.y != (FLOAT)0 || \
	((t_light *)temp->value)->loc.z != (FLOAT)30)
		return (-1);
	if (((t_light *)temp->value)->brightness != (FLOAT)0.7)
		return (-1);
	if (((t_light *)temp->value)->color.r != 255 || \
	((t_light *)temp->value)->color.g != 255 || \
	((t_light *)temp->value)->color.b != 255)
		return (-1);
	temp = get_scene()->plane;
	if (((t_plane *)temp->value)->loc.x != (FLOAT)0 || \
	((t_plane *)temp->value)->loc.y != (FLOAT)0 || \
	((t_plane *)temp->value)->loc.z != (FLOAT)0)
		return (-1);
	if (((t_plane *)temp->value)->color.r != 255 || \
	((t_plane *)temp->value)->color.g != 0 || \
	((t_plane *)temp->value)->color.b != 225)
		return (-1);
	if (((t_plane *)temp->value)->normal.x != (FLOAT)0 || \
	((t_plane *)temp->value)->normal.y != (FLOAT)1 || \
	((t_plane *)temp->value)->normal.z != (FLOAT)0 )
		return (-1);
	printf("\033[32mParsing: valid_whole_file_test passed\n\033[0m");
	return (0);
}

int	whole_parser_test(void)
{
	init_scene();
	if (valid_whole_file_test() == -1)
	{
		printf("\033[31;40mParsing: valid_whole_file_test failed!!!\n\033[0m");
		return (-1);
	}
	return (0);
}
