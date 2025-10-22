/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 01:03:44 by kzarins           #+#    #+#             */
/*   Updated: 2024/11/08 01:03:47 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char **buffer, char *new_line_start);
static char	*return_line(char **buffer, char **current_read, \
		char **new_line_start, int last_line_f);
static int	allocate_buffer(char **buffer);
static int	truncate_buffer(char **buffer, char *new_line_start);

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*current_read;
	int			bytes_read;
	char		*new_line_start;

	if (!buffer)
		if (!allocate_buffer(&buffer))
			return (0);
	current_read = (char *)malloc(BUFFER_SIZE);
	if (!current_read)
		return (free_buffer(&buffer, 0));
	while (1)
	{
		new_line_start = check_for_newline(buffer);
		if (new_line_start)
			return (return_line(&buffer, &current_read, &new_line_start, 0));
		bytes_read = read(fd, current_read, BUFFER_SIZE);
		if (bytes_read == -1 || (bytes_read == 0 && *buffer == '\0') || \
				!add_to_buffer(&buffer, current_read, bytes_read))
			return (free_buffer(&buffer, &current_read));
		if (!check_for_newline(buffer) && bytes_read < BUFFER_SIZE)
			return (return_line(&buffer, &current_read, &new_line_start, 1));
	}
}

static char	*return_line(char **buffer, char **current_read, \
		char **new_line_start, int last_line_f)
{
	free_buffer(current_read, 0);
	*current_read = get_line(buffer, *new_line_start);
	if (!*current_read || last_line_f)
		free_buffer(buffer, 0);
	return (*current_read);
}

static int	allocate_buffer(char **buffer)
{
	*buffer = (char *)malloc(1);
	if (!*buffer)
		return (0);
	**buffer = '\0';
	return (1);
}

static char	*get_line(char **buffer, char *new_line_start)
{
	char	*result;

	if (!new_line_start)
	{
		result = (char *)malloc(str_len(*buffer) + NULL_CHAR_LEN);
		if (!result)
			return (0);
		ft_strlcpygnl(result, *buffer, str_len(*buffer));
		return (result);
	}
	result = (char *)malloc(new_line_start - *buffer + NULL_CHAR_LEN);
	if (!result)
	{
		return (0);
	}
	ft_strlcpygnl(result, *buffer, \
			new_line_start - *buffer);
	if (!truncate_buffer(buffer, new_line_start))
	{
		free(result);
		return (0);
	}
	return (result);
}

static int	truncate_buffer(char **buffer, char *new_line_start)
{
	char	*result;
	int		len;

	len = str_len(*buffer) - (new_line_start - *buffer);
	result = (char *)malloc(len + NULL_CHAR_LEN);
	if (!result)
		return (0);
	ft_strlcpygnl(result, new_line_start, len);
	free_buffer(buffer, 0);
	*buffer = result;
	return (1);
}
