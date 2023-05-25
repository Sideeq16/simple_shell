#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

#define PREFIX "#cisfun$ "


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
	char **env = environ;
	int i = 0;

	for (i = 0; env[i] != NULL; i++)
	{
	/* printf("%s\n", environ[i]);*/
	write(STDOUT_FILENO, env[i], strlen(env[i]));
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
	/* pid_t child_pid; */
	/* int status; */
	/* char *command_path; */

	if (strlen(usr_command) == 0 || strspn(usr_command, " \t")
	== strlen(usr_command))
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
		exit(2);
	}

	if (_strcmp(arg_v[0], "env") == 0)
	{
	print_env();
	free(arg_v);
	return;
	}

	/*command_path = find_command(arg_v[0]);*/
	inner_exec(arg_v);
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
