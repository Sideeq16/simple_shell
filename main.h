#ifndef MY_HEAD_FILES
#define MY_HEAD_FILES

/*void run_cmd(char *command, char **av);*/
extern char **environ;
char **m_token(char *str, const char *delim);
int _strcmp(char *s1, char *s2);
void inner_exec(char **argv);
char *find_command(char *command);
char *build_path(char *dir, char *command);

#endif
