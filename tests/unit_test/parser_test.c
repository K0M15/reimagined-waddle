#include <stdio.h>
#include <errno.h>
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

int	parser_test(void)
{
	if (rgb_converter_test() == -1)
		return (-1);
	return (0);
}
