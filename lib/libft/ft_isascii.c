/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:25:05 by kzarins           #+#    #+#             */
/*   Updated: 2024/10/09 17:21:43 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isascii(int ch)
{
	if (ch >= 0 && ch <= 127)
		return (1);
	return (0);
}

/*
//Start of the test
#include <ctype.h>
#include <stdio.h>
int main(void)
{
	int test_fail_flag = 0;
	printf("Running the test...\n");
	for(int i = 0; i <= 255; i += 2)
	{
		int got = ft_isascii(i);
		int expected = isascii(i);
		if(got == expected)
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
