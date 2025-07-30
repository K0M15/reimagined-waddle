/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 21:41:19 by kzarins           #+#    #+#             */
/*   Updated: 2024/10/22 16:19:42 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy_wo_null(char *dst, const char *str);

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*result;
	char	*loc;

	len = ft_strlen(s1);
	len += ft_strlen(s2);
	result = malloc(len + 1);
	if (!result)
		return (0);
	loc = result;
	loc = ft_strcpy_wo_null(loc, s1);
	loc = ft_strcpy_wo_null(loc, s2);
	*loc = '\0';
	return (result);
}

static char	*ft_strcpy_wo_null(char *dst, const char *str)
{
	while (*str != '\0')
	{
		*dst = *str;
		str++;
		dst++;
	}
	return (dst);
}
