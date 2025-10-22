/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:08:40 by kzarins           #+#    #+#             */
/*   Updated: 2024/10/10 19:07:51 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *str, int search_str)
{
	search_str = search_str % 128;
	while (*str != '\0' && *str != search_str)
		str++;
	if (*str == '\0' && search_str != '\0')
		return (0);
	return ((char *)str);
}
