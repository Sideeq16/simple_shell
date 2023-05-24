#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	while(1)
	{
	char *inputs = NULL;
	size_t n = 0;
	char *args[]= {NULL};
	pid_t child_proc;
	int status;
	extern char **environ;

	printf("#cisfun$ ");
	/*getline(&inputs,&n,stdiin);*/
	
	if (getline(&inputs, &n, stdin) == -1)
	{
		break;
	}

	


	inputs[strlen(inputs) - 1] = '\0';


	if(strcmp(inputs, "exit") == 0)
	{
		break;
	}

	child_proc = fork();

	if (child_proc == -1)
	{	
		perror(argv[0]);
		exit(1);
	}else if (child_proc == 0)
	{
		execve(inputs,args,environ);
		perror(argv[0]);
		exit(1);
	}else {		
		wait(&status);
	}

	free(inputs);
	}

	return (0);

}
