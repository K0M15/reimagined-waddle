#include <stdio.h>
#include <errno.h>
#include "elements.h"
#include "libft.h"
#include "parser.h"

void	cpy_rgb(t_rgb *dst, t_rgb *src)
{
	dst->r = src->r;
	dst->g = src->g;
	dst->b = src->b;
}

static int	validate_rgb_tokens(char **tokens)
{
	char		**temp;
	int			token_count;
	int			len;

	token_count = 0;
	temp = tokens;
	while (*temp)
	{
		len = ft_strlen(*temp);
		if (len > 3 || len == 0)
			return (-1);
		while (len)
			if (!ft_isdigit(*((*temp) + --len)))
				return (-1);
		token_count++;
		temp++;
	}
	if (token_count != 3)
		return (-1);
	return (0);
}

static int	tokens_to_rgb(char **tokens, t_rgb *result)
{
	result->r = atoi(*tokens);
	result->g = atoi(*(tokens + 1));
	result->b = atoi(*(tokens + 2));
	if (result->r > 255 || result->g > 255 || result->b > 255)
		return (-1);
	return (0);
}

void	init_color(t_rgb *color)
{
	color->r = 0;
	color->g = 0;
	color->b = 0;
}

t_rgb	extract_color(const char *input)
{
	char	**tokens;
	t_rgb	color;

	init_color(&color);
	tokens = ft_split(input, ',');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed!\n");
		errno = EINVAL;
		return (color);
	}
	if (validate_rgb_tokens(tokens) == -1)
	{
		errno = EINVAL;
		return (free_tokens(tokens), color);
	}
	if (tokens_to_rgb(tokens, &color) == -1)
	{
		errno = EINVAL;
		return (free_tokens(tokens), color);
	}
	return (free_tokens(tokens), color);
}
