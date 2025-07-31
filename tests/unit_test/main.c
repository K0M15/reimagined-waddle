#include "test.h"

int main(void)
{
	int	ret = 0;

	ret += vec3_test();
	ret += parser_test();
	return (ret);
}
