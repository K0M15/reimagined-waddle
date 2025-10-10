/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:15:02 by kzarins           #+#    #+#             */
/*   Updated: 2024/10/22 16:27:06 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	if (num <= 0)
		return (0);
	while (*str1 && *str2 && num > 1)
	{
		if (*str1 != *str2)
			break ;
		str1++;
		str2++;
		num--;
	}
	return ((int)(*(unsigned char *) str1 - *(unsigned char *) str2));
}
