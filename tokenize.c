#include "shell.h"

/**
 * _tokenize - tokenizes the input of the user
 * @command: character
 * @delim: character
 * Return: array of tokens
 */
char  **_tokenize(char *command, char *delim)
{
	char *tokens;
	char **av;
	int i = 0, j;

	av = malloc(sizeof(char *) * (strlen(command) + 1));
	if (!av)
	{
		perror("Error");
		return (NULL);
	}
	tokens = strtok(command, delim);
	while (tokens != NULL)
	{
		av[i] = strdup(tokens);
		if (av[i] == NULL)
		{
			perror("Tokenize strdup");
			for (j = 0; j < i; j++)
				free(av[j]);
			free(av);
			return (NULL);
		}
	
		tokens = strtok(NULL, delim);
		i++;
	}
	av[i] = NULL;
	return (av);
}
