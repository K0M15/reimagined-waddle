/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:09:44 by kzarins           #+#    #+#             */
/*   Updated: 2024/10/10 19:12:18 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*temp;

	temp = 0;
	c = c % 128;
	while (*str != '\0')
	{
		if (*str == c)
			temp = (char *)str;
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (temp);
}
/*
//Start of the Test
#include <stdio.h>
#include <string.h>

int main (void)
{
	int test_fail_flag = 0;
	printf("Running the test...\n");
	char *test_str[] = {"Test 1", "Test 2", "Test 3",\
   	"TesT 4", "", "Test 6", "Test 7"};
	char test_char[] = {'1', 'e', 'x', 'T', 'a', 0, '\0'};
	for (int i = 0; i < 7; i++)
	{
		char *got = ft_strrchr(test_str[i], test_char[i]);
		char *expected = strrchr(test_str[i], test_char[i]);
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
*/
