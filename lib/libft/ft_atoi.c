/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:53:58 by kzarins           #+#    #+#             */
/*   Updated: 2024/10/10 18:37:47 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

#define MAX_INT 2147483647
#define MIN_INT -2147483648

static int	isspace(int ch);
static void	calculate_num(int *result, const char *str, char *num_negat_flag);

int	ft_atoi(const char *str)
{
	char	num_negat_flag;
	int		result;

	num_negat_flag = 0;
	result = 0;
	while (isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			num_negat_flag = 1;
		str++;
	}
	calculate_num(&result, str, &num_negat_flag);
	return (result);
}

static int	isspace(int ch)
{
	if (ch == ' ' || ch == '\f' || ch == '\n' || \
		ch == '\r' || ch == '\t' || ch == '\v')
		return (1);
	return (0);
}

static void	calculate_num(int *result, const char *str, char *num_negat_flag)
{
	while (*str >= '0' && *str <= '9')
	{
		if (!(*num_negat_flag))
			*result = *result * 10 + (*str - '0');
		else
			*result = *result * 10 - (*str - '0');
		if (!(*num_negat_flag) && *result < 0)
		{
			*result = MIN_INT;
			break ;
		}
		if (*num_negat_flag && *result > 0)
		{
			*result = MAX_INT;
			break ;
		}
		str++;
	}
}
/*
//Start of the Test
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
	int test_fail_flag = 0;
	printf("Running the test...\n");
	char* test_in[] = {"123", "-456", "   789", "123abc",\
   	"", "hello", "2147483648", "-2147483649", "-2147463648"};
	for (int i = 0; i < 9; i++)
	{
		int got = ft_atoi(test_in[i]);
		int expected = atoi(test_in[i]); 
		if (got == expected)
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
