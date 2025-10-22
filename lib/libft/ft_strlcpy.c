/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:58:11 by kzarins           #+#    #+#             */
/*   Updated: 2024/10/12 21:08:38 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dst, const char *str, size_t size)
{
	int	count;

	count = 0;
	if (str == 0 && size <= 0)
		return (0);
	while (size > 1 && *str != '\0')
	{
		*dst = *str;
		size--;
		count++;
		str++;
		dst++;
	}
	while (*str)
	{
		count++;
		str++;
	}
	if (size > 0)
		*dst = '\0';
	return (count);
}
/*
//Start of the Test
#include <stdio.h>
#include <string.h>

int main (void)
{
	int test_fail_flag = 0;
	char* test_str[] = {"hello", "hello", "", NULL, "hello", "hello"};
    	size_t test_size[] = {10, 5, 10, 10, 3, 6};
	char* test_expected[] = {"hello", "hell", "", "", "he", "hello"};
	int test_expected_size[] = {5,5,0,0,5,5};
	printf("Running the test...\n");
	for (int i = 0; i < 6; i++)
	{
		char test_dest1[20], test_dest2[20];
		int got = ft_strlcpy(test_dest1, test_str[i], test_size[i]);
		int expected = test_expected_size[i]; 
		if (got == expected && !strcmp(test_dest1, test_expected[i]))
			printf("Test passed : ");
		else
		{
			printf("Test failed : ");
			test_fail_flag = 1;
		}
		printf("Expected \"%i\", got \"%i\"\n", expected, got);
	}

	if (test_fail_flag == 1)
		printf("TEST FAILED!");
	else
		printf("TEST PASSED!");

	return (0);
}
*/
