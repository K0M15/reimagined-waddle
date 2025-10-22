/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:52:54 by kzarins           #+#    #+#             */
/*   Updated: 2025/07/30 16:16:09 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *to, const void *from, size_t numBytes)
{
	char		*to_temp;
	const char	*from_temp;

	if (from == 0 && to == 0)
		return (to);
	to_temp = to;
	from_temp = from;
	while (numBytes > 0)
	{
		*to_temp = *from_temp;
		to_temp++;
		from_temp++;
		numBytes--;
	}
	return (to);
}
