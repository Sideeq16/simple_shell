#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


char **m_token(char *str, const char *delim) {
    int token_count = 0;
    char **tokens = NULL;
    char *token = strtok(str, delim);

    while (token != NULL) {
        token_count++;
        tokens = realloc(tokens, (token_count + 1) * sizeof(char *));
        tokens[token_count - 1] = token;
        token = strtok(NULL, delim);
    }

    tokens[token_count] = NULL;
    return tokens;
}

 void input_get(void)
{
    char *prefix = "#cisfun$ ";
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, prefix, sizeof(prefix) + 1);
	}
}

void command_mod(char *usr_command, char **arg_v)
{
	pid_t child_pid;
	int status;
	char *command_path;

/*	if (strlen(usr_command) == 0 || strspn(usr_command, " \t") == strlen(usr_command)) */
	if (strlen(usr_command) == 0)
	{
		return;
	}
	arg_v = m_token(usr_command, " ");
	if (arg_v == NULL)
	{
		perror("Tokenize fails");
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
int main(int ac, char **av) {
  (void)ac; 
simple_shell(av);
	
	return (0);
}
