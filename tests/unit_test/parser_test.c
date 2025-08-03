#include <stdio.h>
#include <errno.h>
#include "minirt.h"
#include "settings.h"
#include "elements.h"
#include "parser.h"

static int	rgb_converter_test(void)
{
	t_rgb result = extract_color("255,255,255");
	if (result.r != 255 || result.g != 255 || result.b != 255 || errno != 0)
	{
		printf("Test1: The extract_color('255,255,255') is defective!\n");
		printf("The written values: %d,%d,%d",result.r, result.g, result.b);
		return (-1);
	}
	result = extract_color("0,0,0");
	if (result.r != 0 || result.g != 0 || result.b != 0 || errno != 0)
	{
		printf("Test1: The extract_color('255,255,255') is defective!\n");
		return (-1);
	}
	return (0);
}

int	ft_atof_test(void)
{
	FLOAT result = ft_atof("0.0");
	if (result != (FLOAT)0)
	{
		printf("Test 0: The ft_atof failed on 0.0\n");
		return (-1);
	}
	result = ft_atof("1.0");
	if (result != (FLOAT)1)
	{
		printf("Test 1: The ft_atof failed on 1.0\n");
		return (-1);
	}
	result = ft_atof("0.2");
	if (result != (FLOAT)0.2f)
	{
		printf("Test 2: The ft_atof failed on 0.2\n");
		printf("The value got: %f", result);
		return (-1);
	}
	return (0);
}

int	extract_ambient_light_test(void)
{
	extract_ambient_light("A     0.2    255,255,255");
	extract_ambient_light("A     0.5    0,125,255");

	t_node	*temp = get_scene()->ambient_light;
	if (((t_ambient_light *)temp->value)->lighting_ratio != (FLOAT)0.2)
		return (-1);
	if (((t_ambient_light *)temp->value)->color.r != (int)255 || \
	((t_ambient_light *)temp->value)->color.g != (int)255 || \
	((t_ambient_light *)temp->value)->color.b != (int)255)
		return (-1);
	temp = temp->next;
	if (((t_ambient_light *)temp->value)->lighting_ratio != (FLOAT)0.5)
		return (-1);
	if (((t_ambient_light *)temp->value)->color.r != (int)0 || \
	((t_ambient_light *)temp->value)->color.g != (int)125 || \
	((t_ambient_light *)temp->value)->color.b != (int)255)
		return (-1);
	if (temp->next)
		return (-1);
	printf("\033[32mParsing: ambient_test passed\n\033[0m");
	return (0);
}

int	extract_camera_test(void)
{
	extract_camera("C -50.0,0,20 0,0,1 70");
	extract_camera("C -50.0,100,20    1,0,1    80");

	t_node	*temp = get_scene()->camera;
	if (((t_camera *)temp->value)->loc.x != (FLOAT)-50 || \
	((t_camera *)temp->value)->loc.y != (FLOAT)0 || \
	((t_camera *)temp->value)->loc.z != (FLOAT)20)
		return (-1);
	if (((t_camera *)temp->value)->normal.x != (FLOAT)0 || \
	((t_camera *)temp->value)->normal.y != (FLOAT)0 || \
	((t_camera *)temp->value)->normal.z != (FLOAT)1)
		return (-1);
	if (((t_camera *)temp->value)->fov != (int)70)
		return (-1);
	temp = temp->next;
	if (((t_camera *)temp->value)->loc.x != (FLOAT)-50 || \
	((t_camera *)temp->value)->loc.y != (FLOAT)100 || \
	((t_camera *)temp->value)->loc.z != (FLOAT)20)
		return (-1);
	if (((t_camera *)temp->value)->normal.x != (FLOAT)1 || \
	((t_camera *)temp->value)->normal.y != (FLOAT)0 || \
	((t_camera *)temp->value)->normal.z != (FLOAT)1)
		return (-1);
	if (((t_camera *)temp->value)->fov != (int)80)
		return (-1);
	if (temp->next)
		return (-1);
	printf("\033[32mParsing: camera_test passed\n\033[0m");
	return (0);
}

int	extract_light_test(void)
{
	extract_light("L -40.0,50.0,0.0 0.6 10,0,255");
	extract_light("L -40.0,40.0,-1.0 1   10,20,20");

	t_node	*temp = get_scene()->light;
	if (((t_light *)temp->value)->loc.x != (FLOAT)-40 || \
	((t_light *)temp->value)->loc.y != (FLOAT)50 || \
	((t_light *)temp->value)->loc.z != (FLOAT)0)
		return (-1);
	if (((t_light *)temp->value)->brightness != (FLOAT)0.6)
		return (-1);
	if (((t_light *)temp->value)->color.r != 10 || \
	((t_light *)temp->value)->color.g != 0 || \
	((t_light *)temp->value)->color.b != 255)
		return (-1);
	temp = temp->next;
	if (((t_light *)temp->value)->loc.x != (FLOAT)-40 || \
	((t_light *)temp->value)->loc.y != (FLOAT)40 || \
	((t_light *)temp->value)->loc.z != (FLOAT)-1)
		return (-1);
	if (((t_light *)temp->value)->brightness != (FLOAT)1)
		return (-1);
	if (((t_light *)temp->value)->color.r != 10 || \
	((t_light *)temp->value)->color.g != 20 || \
	((t_light *)temp->value)->color.b != 20)
		return (-1);
	if (temp->next)
		return (-1);
	printf("\033[32mParsing: light_test passed\n\033[0m");
	return (0);
}

int	parser_test(void)
{
	init_scene();
	if (rgb_converter_test() == -1)
		return (-1);
	if (ft_atof_test() == -1)
		return (-1);
	if (extract_ambient_light_test() == -1)
	{
		printf("\033[31;40mParsing: ambient_test failed!!!\n\033[0m");
		return (-1);
	}
	if (extract_camera_test() == -1)
	{
		printf("\033[31;40mParsing: camera_test failed!!!\n\033[0m");
		return (-1);
	}
	if (extract_light_test() == -1)
	{
		printf("\033[31;40mParsing: light_test failed!!!\n\033[0m");
		return (-1);
	}
	return (0);
}
