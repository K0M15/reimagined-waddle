/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:32:31 by kzarins           #+#    #+#             */
/*   Updated: 2024/10/22 14:57:15 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_strcmp(const char *str1, const char *str2, size_t len);

char	*ft_strnstr(const char *heystack, const char *needle, size_t len)
{
	if (*needle == '\0')
		return ((char *)heystack);
	while (*heystack && len > 0)
	{
		if (ft_strcmp(heystack, needle, len) == 0)
			return ((char *)heystack);
		heystack++;
		len--;
	}
	return (0);
}

static int	ft_strcmp(const char *str1, const char *str2, size_t len)
{
	while (*str1 && *str2 && len > 0)
	{
		if (*str1 != *str2)
			break ;
		str1++;
		str2++;
		len--;
	}
	if (!*str2)
		return (0);
	if (len == 0)
		return (1);
	return (*(unsigned char *) str1 - *(unsigned char *) str2);
}
//#include <stdio.h>
//
//int	main(void)
//{
//	printf("%s", ft_strnstr("Some kind of test text.", "test", -1));
//	return (0);
//}
//#include <stdio.h>
//int	main(void)
//{
//
//	printf("%s", ft_strnstr("lorem ipsum dolor sit amet", "dol", 30));
//	return (0);
//}
/*
//Start of the Test
#include <stdio.h>
#include <string.h>

int main (void)
{
	int test_fail_flag = 0;
	printf("Running the test...\n");
	char *test_str[] = {"hello world", "hello world", "hello world",\
   	"", "hello world", "hello world", "hello world", "hello world"};
	char *needle[] = {"world", "foo", "", "world", "hello world",\
   	"hello", "world", "world"};
	int comp_len[] = {11, 11, 11, 0, 11, 11, 11, 5};
	char *expect_results[] = {"world", 0, "hello world", 0, "hello world",\
   	"hello world", "world", 0};
	for (int i = 0; i < 8; i++)
	{
		char *got = ft_strnstr(test_str[i], needle[i], comp_len[i]);
		char *expected = expect_results[i]; 
		if (expected ==  0 && got == 0)
		{
			printf("Test passed : Expected \"NULL\", got \"NULL\"\n");
			continue;
		}
		if (!strcmp(got, expected))
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
