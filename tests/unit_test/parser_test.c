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
		return (-1);
	return (0);
}
