/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:16:11 by kzarins           #+#    #+#             */
/*   Updated: 2024/10/22 19:34:51 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

//By the definition the c should only be max unsigned char,
//but the string.h function does allow multi-character const!
//It should teoretically have this:
//if (c > 255)
//	return (0);
void	*ft_memchr(const void *str, int c, size_t n)
{
	while (*(unsigned char *) str != (unsigned char)c && n > 0)
	{
		n--;
		str++;
	}
	if (n == 0)
		return (0);
	return ((void *)str);
}
/*
//Start of the Test
#include <stdio.h>
#include <string.h>

int main (void)
{
	int test_fail_flag = 0;
	printf("Running the test...\n");
	char* test_str[] = { "hello world", "hello world", "hello world",\
   	"", "abcdefghijklmnopqrstuvwxyz", "hello world", "hello world",\
   	"hello\0world", "héllo world", "hello hello world" };
	int test_char[] = { 'o', 'x', 'h', 'a', 'j', 'd', 'o', '\0', 'é', 'l' };
	int test_len[] = { 5, 11, 11, 0, 26, 11, 100, 11, 11, 15 };
	for (int i = 0; i < 10; i++)
	{
		char *got = ft_memchr(test_str[i], test_char[i], test_len[i]);
		char *expected = memchr(test_str[i], test_char[i], test_len[i]);
		if (got == expected)
			printf("Test passed : ");
		else
		{
			printf("Test failed : ");
			test_fail_flag = 1;
		}
		printf("Expected \"%s\", got \"%s\"\n", expected, got);
	}

	if (test_fail_flag == 1)
		printf("TEST FAILED!");
	else
		printf("TEST PASSED!");

	return (0);
}
//Second test that fails on francinette but does not fail no my PC
#include <stdio.h>
int	main(void)
{
	char	*str;
	char	*result;
	int		size = 15;
	str = (char *)malloc(size);
	ft_strlcpy(str, ":(){ :|: & };:", 15);
	result = ft_memchr(str, '\xde', size);
	printf("%p", result);
}
*/
