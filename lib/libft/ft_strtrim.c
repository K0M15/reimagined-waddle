/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:28:40 by kzarins           #+#    #+#             */
/*   Updated: 2024/10/22 16:27:32 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*create_empty_str(void);
static char			is_in_set(char s1c, char const *set);
static const char	*start_without_set(char const *s1, char const *set);
static const char	*last_without_set(char const *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*start;
	const char	*last;
	char		*result;
	size_t		length;	

	if (!*s1)
		return (create_empty_str());
	start = start_without_set(s1, set);
	if (!start)
		return (create_empty_str());
	last = last_without_set(s1, set);
	length = last - start + 1;
	result = (char *)malloc(length + 1);
	if (!result)
		return (0);
	ft_strlcpy(result, start, length + 1);
	return (result);
}

static char	is_in_set(char s1c, char const *set)
{
	while (*set)
	{
		if (s1c == *set)
			return (1);
		set++;
	}
	return (0);
}

//Will return NULL ptr if the while str consists only of set chars
static const char	*start_without_set(char const *s1, char const *set)
{
	while (*s1 != '\0')
	{
		if (!is_in_set(*s1, set))
			break ;
		s1++;
	}
	if (!*s1)
		return (0);
	return (s1);
}

static const char	*last_without_set(char const *s1, char const *set)
{
	while (*s1 != '\0')
	{
		s1++;
	}
	s1--;
	while (1)
	{
		if (!is_in_set(*s1, set))
			break ;
		s1--;
	}
	return (s1);
}

static char	*create_empty_str(void)
{
	char	*str;

	str = (char *) malloc(1);
	if (!str)
		return (0);
	*str = '\0';
	return (str);
}
