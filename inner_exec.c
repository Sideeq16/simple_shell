#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
 * inner_exec - create a child process
 * @arg_v: argument values
 */

void inner_exec(char **arg_v)
{
	pid_t child_pid;
	int status;
	char *command_path;

	command_path = arg_v[0];
	if (command_path == NULL)
	{
		perror(arg_v[0]);
		exit(2);
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

