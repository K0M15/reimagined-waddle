#include <stdio.h>
#include "vec3.h"

void	vec3_print(const t_vec3 *const input)
{
	printf("The vector values(x,y,z): %f, %f, %f\n", \
			input->x, input->y, input->z);
}
