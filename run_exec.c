#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void run_cmd(char *command, char **av)
{
int status, i;
pid_t pid;

if (strlen(command) == 0 || strspn(command, " \t") == strlen(command))
{
return;
}
av = strtok(command, " ");
if (av == NULL)
{
perror("Tokenization error");
return;
}

pid = fork();
if (pid < 0)
{
perror("Fork");
exit(1);
}
else if (pid == 0)
{
if (execve(command, av, NULL) == -1)
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
exit(1);
}
}
for (i = 0; av[i] != NULL; i++)
{
free(av[i]);
}
free(av);
}
