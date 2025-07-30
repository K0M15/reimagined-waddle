#include <stdio.h>
#include "parser.h"
#include "minirt.h"

static void	print_instructions(void)
{
	printf("The program usage: ./miniRT [scene file]\n");
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		print_instructions();
		return (-1);
	}
	if (pars(argv[1]) == -1)
		return (-1);
	//TODO: Implement after parsing function
	return (0);
}
