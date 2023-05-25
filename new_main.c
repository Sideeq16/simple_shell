#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PREFIX "#cisfun$ "

/**
* *_strcmp - compare two string
* @s1: string 1
* @s2: string 2
* Return: postive or negative value
*/
int _strcmp(char *s1, char *s2)
{
	int i = 0, v1, v2;
	int countS1 = 0, countS2 = 0, n = 0;

	while (*(s1 + countS1) != '\0')
	{
		countS1++;
	}
	while (*(s2 + countS2) != '\0')
	{
		countS2++;
	}

	n = countS1 > countS2 ? countS1 : countS2;

	while (i < n)
	{
		if (*(s1 + i) != *(s2 + i))
		{
			v1 = (int) *(s1 + i);
			v2 = (int) *(s2 + i);
			if (v1 > v2)
			{
				return (v1 - v2);
			}
			else if (v1 < v2)
			{
				return (v1 - v2);
			}
		}
		i++;
	}

	return (0);
}

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
	token = strtok(NULL, delim);
	}

	tokens[token_count] = NULL;
	return (tokens);
}

/**
 * input_get - get user input
 */
void input_get(void)
{
	/*char *prefix = "#cisfun$ ";*/
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, PREFIX, sizeof(PREFIX) - 1);
	}
}

/**
 * print_env - get user input
 */
void print_env(void)
{
	extern char **environ;
	int i = 0;

	for (i = 0; environ[i] != NULL; i++)
	{
	/* printf("%s\n", environ[i]);*/
	write(STDOUT_FILENO, environ[i], strlen(environ[i]));
	write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * command_mod - run command method
 * @arg_v: argument values
 * @usr_command: user command
 * Return: zero or fail
 */
void command_mod(char *usr_command, char **arg_v)
{
	pid_t child_pid;
	int status;
	char *command_path;

	if (strlen(usr_command) == 0 || strspn(usr_command, " \t") == strlen(usr_command))
	{
		return;
	}
	arg_v = m_token(usr_command, " ");
	if (arg_v == NULL)
	{
		perror("Tokenize fails");
		return;
	}

	if (_strcmp(arg_v[0], "exit") == 0)
	{
		free(arg_v);
		free(usr_command);
		exit(0);
	}

	if (_strcmp(arg_v[0], "env") == 0)
	{
	print_env();
	free(arg_v);
	return;
	}

	/*command_path = find_command(arg_v[0]);*/
	command_path = arg_v[0];
	if (command_path == NULL)
	{
		perror(arg_v[0]);
		return;
	}
	child_pid = fork();
	if (child_pid < 0)
	{
		perror("fail to fork");
		free(command_path);
		exit(1);
	}
	else if (child_pid == 0)
	{
		if (execve(command_path, arg_v, NULL) == -1)
		{
			perror(arg_v[0]);
			exit(1);
		}
	}
	else
	{
		if (waitpid(child_pid, &status, 0) == -1)
		{
			perror("err waitpid");
			free(command_path);
			exit(1);
		}
	}
	free(arg_v);
}


/**
 * simple_shell - simple shell program
 * @av: argument param
 */
void simple_shell(char **av)
{
	char *inputs = NULL;
	size_t inputs_len = 0;

	while (1)
	{
		input_get();
		fflush(stdout);
		if (getline(&inputs, &inputs_len, stdin) == -1)
		{
			free(inputs);
			exit(0);
		}
		inputs[strcspn(inputs, "\n")] = '\0';
		command_mod(inputs, av);
		free(inputs);
		inputs = NULL;
	}
}

/**
 * main - shell program
 * @ac: argument counter
 * @av: argument vector
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	(void)ac;
	simple_shell(av);

	return (0);
}
