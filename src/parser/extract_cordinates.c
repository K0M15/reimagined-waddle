#include <stdio.h>
#include <errno.h>
#include "elements.h"
#include "libft.h"
#include "parser.h"

void	cpy_loc(t_point *dst, t_point *src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

static int	tokens_to_loc(char **tokens, t_point *result)
{
	result->x = atof(*tokens);
	if (errno)
		return (-1);
	result->y = atof(*(tokens + 1));
	if (errno)
		return (-1);
	result->z = atof(*(tokens + 2));
	if (errno)
		return (-1);
	return (0);
}

static void	init_loc(t_point *loc)
{
	loc->x = 0;
	loc->y = 0;
	loc->z = 0;
}

t_point	extract_loc(const char *input)
{
	char	**tokens;
	t_point	location;

	init_loc(&location);
	tokens = ft_split(input, ',');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed!\n");
		errno = EINVAL;
		return (location);
	}
	if (tokens_to_loc(tokens, &location) == -1)
	{
		errno = EINVAL;
		return (free_tokens(tokens), location);
	}
	return (free_tokens(tokens), location);
}
