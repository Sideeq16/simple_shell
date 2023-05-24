#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

/**
 * main - simple shell program
 * Return: zero on successful
 */
int main(void)
{
char *command;
int status;

while (1)
{
printf("$ ");
fflush(stdout);

command = malloc(1024);
getline(command, 1024, stdin);

	/* Check for end of file condition */
if (feof(stdin))
{
free(command);
break;
}

	/* Strip the newline character from the end of the command */
command[strcspn(command, "\n")] = '\0';

	/* Try to execute the command */
pid_t pid = fork();
if (pid == 0)
{
execve(command, NULL, environ);
	/* If execve returns, the command could not be found */
perror("execve");
exit(1);
}
else
{
wait(&status);
}

free(command);
}

return (0);
}
