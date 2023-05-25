#include <unistd.h>
#include <stdlib.h>

#define READ_BUFFER_SIZE 1024

ssize_t my_getline(char **input_line, size_t *input_line_size, FILE *input_stream)
{
    static char read_buffer[READ_BUFFER_SIZE];
    static int read_buffer_pos = 0;
    static int read_buffer_len = 0;

    if (input_line == NULL || input_line_size == NULL || input_stream == NULL)
    {
        return -1;
    }

    if (*input_line == NULL)
    {
        *input_line = malloc(READ_BUFFER_SIZE);
        if (*input_line == NULL)
        {
            return -1;
        }
        *input_line_size = READ_BUFFER_SIZE;
    }

    int input_line_pos = 0;
    while (1)
    {
        if (read_buffer_pos >= read_buffer_len)
        {
            read_buffer_len = read(fileno(input_stream), read_buffer, READ_BUFFER_SIZE);
            read_buffer_pos = 0;
        }

        if (read_buffer_len == 0)
        {
            break;
        }

        if (read_buffer_len < 0)
        {
            return -1;
        }

        char current_char = read_buffer[read_buffer_pos++];
        (*input_line)[input_line_pos++] = current_char;

        if (input_line_pos >= *input_line_size)
        {
            size_t new_input_line_size = *input_line_size * 2;
            char *new_input_line = realloc(*input_line, new_input_line_size);
            if (new_input_line == NULL)
            {
                return -1;
            }
            *input_line = new_input_line;
            *input_line_size = new_input_line_size;
        }

        if (current_char == '\n')
        {
            break;
        }
    }

    (*input_line)[input_line_pos] = '\0';
    return input_line_pos;
}
