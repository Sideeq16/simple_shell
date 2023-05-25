#include <string.h>

/**
 * my_strtok - real token
 * @input_str: input string
 * @separator: seperator
 * Return: string tokenized
 */
char *my_strtok(char *input_str, const char *separator)
{
	static char *remaining_str;
	char *current_token;

	if (input_str != NULL)
	{
	remaining_str = input_str;
	}

	if (remaining_str == NULL)
	{
	return (NULL);
	}

	current_token = remaining_str;

	while (*remaining_str != '\0')
	{
	if (strchr(separator, *remaining_str) != NULL)
	{
	*remaining_str = '\0';
	remaining_str++;
	break;
	}
	remaining_str++;
	}

	if (*current_token == '\0')
	{
	current_token = NULL;
	}

	return (current_token);
}
