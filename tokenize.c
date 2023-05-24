#include "shell.h"


/**
 * m_token - tokenize
 * @command: chacters pass
 * @delim: seperator
 * Return: array of tokens
*/
char **m_token(char *str, char *delim)
{
	int token_count = 0;
	char **tokens = NULL;
	char *token = strtok(str, delim);

	while (token != NULL)
	{
		token_count++;
		tokens = realloc(tokens, (token_count+1) * sizeof(char *));
		tokens[token_count - 1] = token;
		token = strtok(NULL, delim);
	}
	tokens[token_count]= NULL;
	return tokens;
}

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
