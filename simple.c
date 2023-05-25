#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 80
#define READ_BUFFER_SIZE 1024

static char read_buffer[READ_BUFFER_SIZE];
static int read_buffer_pos = 0;
static int read_buffer_len = 0;

static int read_next_char(char *current_char, FILE *input_stream)
{
    if (read_buffer_pos >= read_buffer_len)
    {
        read_buffer_len = read(fileno(input_stream),
                               read_buffer,
                               READ_BUFFER_SIZE);
        read_buffer_pos = 0;
    }

    if (read_buffer_len == 0)
        return 0;

    if (read_buffer_len < 0)
        return -1;

    *current_char = read_buffer[read_buffer_pos++];
    return 1;
}

ssize_t my_getline(char **input_line,
                   size_t *input_line_size,
                   FILE *input_stream)
{
    if (input_line == NULL || input_line_size == NULL || input_stream == NULL)
        return -1;

    if (*input_line == NULL)
    {
        *input_line = malloc(READ_BUFFER_SIZE);
        if (*input_line == NULL)
            return -1;
        *input_line_size = READ_BUFFER_SIZE;
    }

    int input_line_pos = 0;
    while (1)
    {
        char current_char;
        int result = read_next_char(&current_char, input_stream);
        if (result <= 0)
            break;

        (*input_line)[input_line_pos++] = current_char;

        if (input_line_pos >= *input_line_size)
        {
            size_t new_input_line_size = *input_line_size * 2;
            char *new_input_line =
                realloc(*input_line, new_input_line_size);
            if (new_input_line == NULL)
                return -1;
            *input_line = new_input_line;
            *input_line_size = new_input_line_size;
        }

        if (current_char == '\n')
            break;
    }

    (*input_line)[input_line_pos] = '\0';
    return input_line_pos;
}

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
                if (!isatty(fileno(stdin))) {
                    should_run = 0;
                }
            }
        }
    }

    free(input);
    return 0;
}
