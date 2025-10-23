/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:26:52 by kzarins           #+#    #+#             */
/*   Updated: 2024/10/09 18:31:42 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isprint(int ch)
{
	if (ch >= 32 && ch <= 126)
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
		int got = ft_isprint(i);
		int expected = isprint(i);
		if ((got > 0 && expected > 0) || (got == 0 && expected == 0))
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
