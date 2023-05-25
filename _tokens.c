#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "main.h"

/**
 * m_token - tokenize
 * @str: strings
 * @delim: delimeter
 * Return: tokenize strings
 */
char **m_token(char *str, const char *delim)
{
	int token_count = 0;
	char **tokens = NULL;
	char *token = strtok(str, delim);

	while (token != NULL)
	{
	token_count++;
	tokens = realloc(tokens, (token_count + 1) * sizeof(char *));
	tokens[token_count - 1] = token;
	token = my_strtok(NULL, delim);
	}

	tokens[token_count] = NULL;
	return (tokens);
}

