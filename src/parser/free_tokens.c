#include <stdlib.h>

void	free_tokens(char **tokens)
{
	while (*tokens)
	{
		free(*tokens);
		(*tokens)++;
	}
	free(tokens);
	tokens = 0;
}
