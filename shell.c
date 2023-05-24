#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
 * main - simple shell program
 * @ac: count commad args
 * @av: store command value
 * Return: zero on successful
 */
int main(int ac, char **av)
{
char *line = NULL;
int status;
size_t len = 0;
ssize_t nread;
char *argv[2];
char *err_msg = ": No such file or directory\n";
int is_interative = isatty(STDIN_FILENO);
argv[1] = NULL;
(void)ac;

while (1)
{
if (is_interative)
{
	write(STDOUT_FILENO, "$ ", 2);
	fflush(stdout);
}
/*write(STDOUT_FILENO, "($) ", 4);*/
nread = getline(&line, &len, stdin);
if (nread == -1)
{
	break;
}
line[strcspn(line, "\n")] = '\0';
argv[0] = line;
if (fork() == 0)
{
execve(line, argv, environ);
write(STDERR_FILENO, av[0], strlen(av[0]));
write(STDERR_FILENO, err_msg, strlen(err_msg));
exit(1);
}
else
{
wait(&status);
}
}
free(line);
return (0);
}
