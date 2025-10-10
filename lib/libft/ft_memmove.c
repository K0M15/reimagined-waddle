/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:55:34 by kzarins           #+#    #+#             */
/*   Updated: 2025/07/30 16:16:50 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *to, const void *from, size_t numBytes)
{
	char		*to_temp;
	const char	*from_temp;

	to_temp = to;
	from_temp = from;
	if (from == to)
		return (to);
	if ((from - to) < 0)
	{
		while (numBytes > 0)
		{
			numBytes--;
			*(to_temp + numBytes) = *(from_temp + numBytes);
		}
		return (to);
	}
	while (numBytes > 0)
	{
		*to_temp = *from_temp;
		to_temp++;
		from_temp++;
		numBytes--;
	}
	return (to);
}
