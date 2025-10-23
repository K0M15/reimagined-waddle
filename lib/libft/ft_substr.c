/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:27:49 by kzarins           #+#    #+#             */
/*   Updated: 2024/10/22 16:32:44 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	char	*result;

	if (ft_strlen(s) < start)
	{
		result = (char *) malloc(1);
		if (!result)
			return (0);
		*result = '\0';
		return (result);
	}
	len_s = ft_strlen(s + start);
	if (len_s > len)
		len_s = len;
	len_s++;
	result = (char *) malloc(len_s);
	if (!result)
		return (0);
	ft_strlcpy(result, s + start, len_s);
	return (result);
}
//
//#include <stdio.h>
//int	main(void)
//{
//	char	*result = ft_substr("", 1, 1);
//
//	printf("%s", result);
//	return (0);
//}
