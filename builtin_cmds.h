// #ifndef UTILS_H
// #define UTILS_H

// #include <stdlib.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <sys/stat.h>
// #include <string.h> 

#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define SIZE 255

typedef enum{ARG_CD} ArgType;

//b_fn table hash map structure
typedef struct Command{
    const char *cmd; //!!! should this be the function pointer instead?
    void *func; //generic pointer to be cast b4 calling
    ArgType expected_type;
    size_t arg_size;
}Command;

Command table[] = {
    {"cd", run_cd},
    // {"echo", run_echo},
    // {"setenv", run_setenv},
    // {"unsetenv", run_unsetenv},
    // {"env", run_env},
    // {"exit", run_exit},
    // {"pwd", run_pwd},
    // {"which", run_which}
};




void no_command(const char *com_string);
int is_builtin(char *string);
void run_command(const char *cmd);

    // void malloc_error();
// int compare_ints(const void *a, const void *b);
// int find_nl_index(const char *s);
// char *combine_str_and_free_first(char *s1, char *s2, int len2);
// void init_my_readline();
// char *my_readline(int fd);
// void free_string_array(char **names, int num_names);

// #endif