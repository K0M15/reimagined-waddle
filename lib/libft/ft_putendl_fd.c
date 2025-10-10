/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:15:56 by kzarins           #+#    #+#             */
/*   Updated: 2024/10/22 16:15:59 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	*result;
	int		len;

	result = ft_strjoin(s, "\n");
	if (!result)
		return ;
	len = ft_strlen(result);
	write(fd, result, len);
	free(result);
}
