#include "settings.h"
#include "vec3.h"
#include <stdlib.h>
#include <stdio.h>

int vec3_test(void)
{
	vec3 a = (vec3){.x=1, .y=1, .z=2};
	vec3 b = (vec3){.x=2, .y=3, .z=4};
	FLOAT dot_prod = vec3_dot_product(&a,&b);
	vec3 *cross_prod = vec3_cross_procuct_r(&a,&b);
	printf("The vec3 a:\n");
	vec3_print(&a);
	printf("The vec3 b:\n");
	vec3_print(&b);
	printf("The dot product is: %f\n", dot_prod);
	printf("The cross product is: ");
	vec3_print(cross_prod);

	free(cross_prod);
	return (1);
}
