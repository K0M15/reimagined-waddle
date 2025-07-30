#include <errno.h>
#include "elements.h"
#include "libft.h"

void	cpy_rgb(t_rgb *dst, t_rgb *src)
{
	dst->color.r = src->r;
	dst->color.g = src->g;
	dst->color.b = src->b;
}

static int	validate_rgb_tokens(const char **tokens)
{
	const char	**temp;
	int		token_count;

	token_count = 0;
	temp = tokens;
	//TODO: The loop should be optimized for checking!!!
	while (temp)
	{
		token_count++, temp++;
	}
	if (token_count != 3)
		return (-1);
	temp = tokens;
}

t_rgb	extract_color(const char *input)
{
	char **tokens;
	int	iter;
	t_rgb	color;
	
	tokens = ft_split(input, ',');
	if (!tokens)
	{
		printf("Could not split the tokens or malloc failed!\n");
		return (-1);
	}
	iter = 0;
	while (iter < 3)
	{
		if (validate_rgb_str(tokens[iter]) == -1)
		{
			errno = EINVAL;
			return (-1);
		}
	}
}
