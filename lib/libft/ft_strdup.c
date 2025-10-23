/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:06:40 by kzarins           #+#    #+#             */
/*   Updated: 2024/10/22 16:18:30 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcpy(char *dst, const char *str);

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*ptr_ret;

	len = ft_strlen(s1);
	ptr_ret = (char *) malloc(len + 1);
	if (!ptr_ret)
		return (0);
	ft_strcpy(ptr_ret, s1);
	return ((void *)ptr_ret);
}

static void	ft_strcpy(char *dst, const char *str)
{
	while (*str != '\0')
	{
		*dst = *str;
		str++;
		dst++;
	}
	*dst = '\0';
}
//#include <stdio.h>
//int	main(void)
//{
//	char	*ptr;
//
//	ptr = ft_strdup("Something");
//	printf("%s", ptr);
//	return (0);
//}
