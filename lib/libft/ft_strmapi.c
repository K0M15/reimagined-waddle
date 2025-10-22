/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:21:23 by kzarins           #+#    #+#             */
/*   Updated: 2024/10/22 16:21:29 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	index;

	result = (char *) malloc(ft_strlen(s) + 1);
	if (!result)
		return (0);
	index = 0;
	while (*s)
	{
		*(result + index) = f(index, *s);
		index++;
		s++;
	}
	*(result + index) = '\0';
	return (result);
}
