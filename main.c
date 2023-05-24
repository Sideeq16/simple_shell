#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
 * main - simple shell program
 * @argc: number of argument
 * @argv: arugment passed
 * Return: zero on successful
 */
int main(int argc, char *argv[])
{
	size_t n = 0;
	char *inputs = NULL;
	pid_t child_proc;
	int status, is_interative = isatty(STDIN_FILENO);
	(void)argc;

	while (1)
	{
		if (is_interative)
		{
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		fflush(stdout);
		}

		if (getline(&inputs, &n, stdin) == -1)
			break;

		inputs[strlen(inputs) - 1] = '\0';
		/*if (strcmp(inputs, "exit") == 0)break;*/
		child_proc = fork();
		if (child_proc < 0)
		{
			perror(argv[0]);
			exit(1);
		}
		else if (child_proc == 0)
		{
			execve(inputs, argv, NULL);
			perror(argv[0]);
			free(inputs);
			exit(1);
		}
		else
		{
			waitpid(child_proc, &status, 0);
		}

	}
	free(inputs);
	return (0);
}
