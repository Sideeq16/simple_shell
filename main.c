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
	/*pid_t child_proc;*/
	int is_interative = isatty(STDIN_FILENO);
	(void)argc;

	while (1)
	{
		if (is_interative)
		{
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		fflush(stdout);
		}

		if (getline(&inputs, &n, stdin) == -1)
		{
			free(inputs);
			exit(0);
		}

		/*inputs[strlen(inputs) - 1] = '\0';*/
		inputs[strcspn(inputs, "\n")] = '\0';
		run_cmd(inputs, argv);
		free(inputs);


	}
	free(inputs);
	return (0);
}
