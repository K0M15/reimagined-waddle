/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzarins <kzarins@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:18:01 by kzarins           #+#    #+#             */
/*   Updated: 2024/10/22 16:46:03 by kzarins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count_f(const char *s, char delim);
static int	count_word_char(const char *s, char del);
static int	add_word(char **result, const char **s, char c, int current_word);
static void	free_memory(char **result, int current_word);

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;
	int		current_word;

	word_count = word_count_f(s, c);
	current_word = 0;
	result = (char **) malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (0);
	while (current_word < word_count)
	{
		if (!add_word(result, &s, c, current_word))
			return (0);
		current_word++;
	}
	*(result + current_word) = 0;
	return (result);
}

static int	word_count_f(const char *s, char delim)
{
	char	in_word;
	int		word_count;

	if (!s)
		return (0);
	in_word = 0;
	word_count = 0;
	while (*s)
	{
		if (*s != delim && !in_word)
		{
			in_word = 1;
			word_count++;
		}
		else if (*s == delim && in_word)
			in_word = 0;
		s++;
	}
	return (word_count);
}

static int	count_word_char(const char *s, char del)
{
	int	char_count;

	char_count = 0;
	while (*s == del)
		s++;
	while (*s != del && *s)
	{
		char_count++;
		s++;
	}
	return (char_count);
}

static int	add_word(char **result, const char **s, char c, int current_word)
{
	int	word_char_c;

	word_char_c = count_word_char(*s, c);
	*(result + current_word) = (char *) malloc(word_char_c + 1);
	if (*(result + current_word) == 0)
	{
		free_memory(result, current_word);
		return (0);
	}
	while (**s == c)
		*s = *s + 1;
	ft_strlcpy(*(result + current_word), *s, word_char_c + 1);
	*s = *s + word_char_c;
	return (1);
}

static void	free_memory(char **result, int current_word)
{
	while (current_word >= 0)
	{
		free(*(result + current_word));
		current_word--;
	}
	free(result);
}
//#include <stdio.h>
//int	main(void)
//{
////	char	*test = "aThis   is some literal string";
////	char	test_c = ' ';
////	char	**holder = (char **) malloc(3);
////	const char	*sentence1 = "third    asdf  ";
////	add_word(holder, &sentence1, ' ', 0);
////	add_word(holder, &sentence1, ' ', 1);
////	//Test word count function
////	//printf("%i", word_count_f("Some times it sucks", ' '));
////	//Test char count function
////	//printf("%i", count_word_char(test + 5, test_c));
////	//test add word functiono	
////	printf("%s\n", *(holder));
////	printf("%s\n", *(holder + 1));
////	//Test free mem funcion
////	free_memory(holder, 1);
//char	**holder;
//holder = ft_split("lorem ipsum dolor sit amet,
//		 consectetur adipiscing elit. Sed non risus. Suspendisse", ' ');
//int	i = 0;
//while (*(holder + i))
//{
//	printf("%s\n", *(holder + i));
//i++;
//}
//	return (0);
//}
