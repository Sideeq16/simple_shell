#ifndef MY_HEAD_FILES
#define MY_HEAD_FILES

/*void run_cmd(char *command, char **av);*/
extern char **environ;
char **m_token(char *str, const char *delim);
int _strcmp(char *s1, char *s2);
void inner_exec(char **argv);
ssize_t my_getline(char **input_line, size_t *input_line_size, FILE *input_stream);
char *my_strtok(char *input_str, const char *separator);
/*static int read_next_char(char *current_char, FILE *input_stream);*/

#endif
