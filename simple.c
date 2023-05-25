#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "main.h"

#define MAX_LINE 80
#define READ_BUFFER_SIZE 1024

int main(void)
{
    char *args[MAX_LINE/2 + 1];
    int should_run = 1;
    char *input = NULL;
    size_t input_size = 0;

    while (should_run) {
        if (isatty(fileno(stdin))) {
            printf("osh>");
            fflush(stdout);
        }

        ssize_t input_len = my_getline(&input, &input_size, stdin);
       if (input_len <= 0) {
            should_run = 0;
            break;
        }
        input[input_len - 1] = '\0';

        if (strcmp(input, "exit") == 0) {
            should_run = 0;
        } else {
            args[0] = strtok(input, " ");
            int i = 0;
            while (args[i] != NULL) {
                i++;
                args[i] = strtok(NULL, " ");
            }

            pid_t pid = fork();
            if (pid == 0) {
                execvp(args[0], args);
                exit(0);
            } else {
                wait(NULL);
               /* if (!isatty(fileno(stdin))) {
                    should_run = 0;
                }*/
            }
        }
    }

    free(input);
    return 0;
}
