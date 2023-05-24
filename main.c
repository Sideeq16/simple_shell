#include "shell.h"

/**
 * handle_interrupt - handles Ctrl+C
 * @signum: integer
 * Return: void
 */
void handle_interrupt(int signum)
{
	(void)signum;

}
/**
 * exe_cmd1 - executes command without command line argument and path
 * @command: command to execute
 * @av: argument vector
 * Reurn: void
 */
void exe_cmd1(char *command, char **av)
{
	char *command_path;
	int status;
	pid_t pid;

	if (strlen(command) == 0 || strspn(command, " \t") == strlen(command))
	{
		return;
	}
	av = m_token(command, " ");
	if (av == NULL)
	{
		perror("Tokenization error");
		return;
	}
	/*command_path = find_command(av[0]);*/
	command_path = av[0];
	if (command_path == NULL)
	{
		perror(av[0]);
		return;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Fork");
		free(command_path);
		exit(1);
	}
	else if (pid == 0)
	{
		if (execve(command_path, av, NULL) == -1)
		{
			perror(av[0]);
			exit(1);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			free(command_path);
			exit(1);
		}
	}
	/*for (i = 0; av[i] != NULL; i++){free(av[i]);}*/
	free(av);
}
/**
 * shell_loop - performs the loop operation
 * @av: argument vector
 * Return: void
 */
void shell_loop(char **av)
{
	char *command = NULL;
	size_t command_length = 0;

	/* signal(SIGINT, handle_interrupt); */

	while (1)
	{
		prompt();
		fflush(stdout);
		if (getline(&command, &command_length, stdin) == -1)
		{
			free(command);
			exit(0);
		}
		command[strcspn(command, "\n")] = '\0';
		exe_cmd1(command, av);
		free(command);
		command = NULL;
	}
}

/**
 * main - entry point of the shell
 * @ac: argument counter
 * @av: argument vector
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	if (ac > 1)
	{
		exe_cmd1(av[1], av);
		return (0);
	}
	else
	{
		shell_loop(av);
	}
	return (0);
}
