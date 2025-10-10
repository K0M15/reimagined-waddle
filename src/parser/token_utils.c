#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "settings.h"
#include <stdio.h>

void	free_tokens(char **tokens)
{
	char	**temp;

	temp = tokens;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(tokens);
}

int	token_ammount(char **tokens)
{
	char	**temp;
	int	count;

	count = 0;
	temp = tokens;
	while (*temp)
	{
		temp += 1;
		count++;
	}
	return (count);
}

FLOAT	ft_atof(const char *input)
{
	FLOAT	result;
	FLOAT	fraction_loc;
	int	sign;

	result = 0;
	sign = 1;
	if (*input == '-')
	{
		sign = -1;
		input++;
	}
	if (!ft_isdigit(*input))
	{
		errno = EINVAL;
		return (result);
	}
	while (*input && ft_isdigit(*input))
	{
		result = result * 10 + (*input - '0');
		input++;
	}
	if (!*input)
		return (result * sign);
	if (*input != '.' || !ft_isdigit(*(input + 1)))
	{
		errno = EINVAL;
		return (result);
	}
	input++;
	fraction_loc = (FLOAT)10;
	while (*input && ft_isdigit(*input))
	{
		result += (*input - '0') / fraction_loc;
		fraction_loc *= 10;
		input++;
	}
	if (*input)
		errno = EINVAL;
	return (sign * result);
}
