#include <stdio.h>
#include <errno.h>
#include "elements.h"
#include "libft.h"
#include "parser.h"
#include "ftvec3.h"

void	cpy_normal(t_vec3 *dst, t_vec3 *src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

static int	tokens_to_normal(char **tokens, t_vec3 *result)
{
	result->x = ft_atof(*tokens);
	if (errno || result->x > (double)1 || result->x < (double)-1)
		return (-1);
	result->y = ft_atof(*(tokens + 1));
	if (errno || result->y > (double)1 || result->y < (double)-1)
		return (-1);
	result->z = ft_atof(*(tokens + 2));
	if (errno || result->z > (double)1 || result->z < (double)-1)
		return (-1);
	return (0);
}

static void	init_normal(t_vec3 *normal)
{
	normal->x = 0;
	normal->y = 0;
	normal->z = 0;
}

t_vec3	extract_normal(const char *input)
{
	char		**tokens;
	t_vec3	normal;

	init_normal(&normal);
	tokens = ft_split(input, ',');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed!\n");
		errno = EINVAL;
		return (normal);
	}
	if (tokens_to_normal(tokens, &normal) == -1)
	{
		errno = EINVAL;
		return (free_tokens(tokens), normal);
	}
	normal = ftvec3_normalize(normal);
	return (free_tokens(tokens), normal);
}
