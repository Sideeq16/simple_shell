#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/**
 * main - simple shell program
 * Return: zero on successful
 */
int main(int ac, char **av) {
char *line = NULL;
int status;
size_t len = 0;
ssize_t nread;
char *argv[2];
argv[1] = NULL;
char *err_msg = ": No such file or directory\n";

while (1) {
write(STDOUT_FILENO, "$ ", 2);
nread = getline(&line, &len, stdin);
if (nread == -1) {
write(STDOUT_FILENO, "\n", 1);
exit(0);
}
line[strcspn(line, "\n")] = '\0';
argv[0] = line;
if (fork() == 0)
{
execve(line, argv, NULL);
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
return 0;
}
