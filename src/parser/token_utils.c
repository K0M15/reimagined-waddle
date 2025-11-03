/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:31:06 by kzarins           #+#    #+#             */
/*   Updated: 2025/11/03 19:38:58 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "libft.h"
#include "object.h"

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
	int		count;

	count = 0;
	temp = tokens;
	while (*temp)
	{
		temp += 1;
		count++;
	}
	return (count);
}

double	extract_fraction(const char *input, double *result, int sign)
{
	double	fraction_loc;

	if (*input != '.' || !ft_isdigit(*(input + 1)))
	{
		errno = EINVAL;
		return (*result);
	}
	input++;
	fraction_loc = (double)10;
	while (*input && ft_isdigit(*input))
	{
		*result += (*input - '0') / fraction_loc;
		fraction_loc *= 10;
		input++;
	}
	if (*input)
		errno = EINVAL;
	return (sign * *result);
}

double	ft_atof(const char *input)
{
	double	result;
	int		sign;

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
	return (extract_fraction(input, &result, sign));
}

int	init_material(t_obj *obj)
{
	obj->mat.reflectivity = 0.2;
	obj->mat.scatter = 0.2;
	obj->mat.is_emitting = 0;
	obj->mat.tex = NULL;
	obj->mat.bump = NULL;
	return (0);
}
