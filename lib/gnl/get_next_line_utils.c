/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 05:47:41 by kzarins           #+#    #+#             */
/*   Updated: 2024/11/07 23:20:43 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		add_to_buffer(char **buffer, char *current_read, int bytes_read);
int		str_len(char *str);
void	ft_strlcpy(char *result, char *buffer, int len);
char	*free_buffer(char **buffer, char **buffer2);
char	*check_for_newline(char *buffer);

//If theres are no read bytes the buffer does not get changed
//In that case the function returns -1
int	add_to_buffer(char **buffer, char *current_read, int bytes_read)
{
	char	*result;
	int		len_counter;
	int		iter;

	if (!bytes_read)
		return (-1);
	result = (char *) malloc(str_len(*buffer) + bytes_read + NULL_CHAR_LEN);
	if (!result)
		return (0);
	len_counter = 0;
	while (*(*buffer + len_counter))
	{
		*(result + len_counter) = *(*buffer + len_counter);
		len_counter++;
	}
	iter = 0;
	while (iter++ < bytes_read)
	{
		*(result + len_counter) = *(current_read + iter - 1);
		len_counter++;
	}
	*(result + len_counter) = '\0';
	free(*buffer);
	*buffer = result;
	return (iter);
}

int	str_len(char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

void	ft_strlcpy(char *result, char *buffer, int len)
{
	*(result + len) = '\0';
	len--;
	while (len >= 0)
	{
		*(result + len) = *(buffer + len);
		len--;
	}
	return ;
}

char	*free_buffer(char **buffer, char **buffer2)
{
	if (*buffer)
		free (*buffer);
	*buffer = 0;
	if (buffer2)
	{
		if (*buffer2)
			free (*buffer2);
		*buffer2 = 0;
	}
	return (0);
}

char	*check_for_newline(char *buffer)
{
	while (*buffer)
	{
		if (*buffer == '\n')
			return (++buffer);
		buffer++;
	}
	return (0);
}
