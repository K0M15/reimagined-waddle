/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:47:11 by kzarins           #+#    #+#             */
/*   Updated: 2025/07/30 16:17:10 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	char	*str_temp;

	str_temp = str;
	while (n > 0)
	{
		*str_temp = (char) c;
		n--;
		str_temp++;
	}
	return (str);
}
