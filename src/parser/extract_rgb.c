#include <stdio.h>
#include <errno.h>
#include "elements.h"
#include "libft.h"
#include "parser.h"

void	cpy_rgb(t_vec3 *dst, t_vec3 *src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
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

static int	tokens_to_rgb(char **tokens, t_vec3 *result)
{
	result->x = ft_atoi(*tokens);
	result->y = ft_atoi(*(tokens + 1));
	result->z = ft_atoi(*(tokens + 2));
	if (result->x > 255 || result->y > 255 || result->z > 255)
		return (-1);
	result->x /= 255;
	result->y /= 255;
	result->z /= 255;
	return (0);
}

void	init_color(t_vec3 *color)
{
	color->x = 0;
	color->y = 0;
	color->z = 0;
}

t_vec3	extract_color(const char *input)
{
	char	**tokens;
	t_vec3	color;

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
