#ifndef BUILTIN_CMDS_H
#define BUILTIN_CMDS_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h> 
#include <stdio.h>
#include "utils.h"

#define MAX_STR_LEN 255
#define BUF_SIZE 255
#define MAX_PATH_LEN 1024

extern char **environ;

typedef void (*CommandFunc)(int, void *);

typedef enum{
    TOK_CD = 2,
    TOK_ECHO = 2,
    TOK_EXPORT = 2,  //ARG_SETENV = 4,
    TOK_UNSET = 2,   //ARG_UNSETENV = 2,
    TOK_ENV = 1,
    TOK_EXIT = 1, 
    TOK_PWD = 1,
    TOK_WHICH = 2 //>>>needs to be variable... args until null... maybe parse char * pointers until then
} TokType;

typedef void (*CommandFunc)(int, void *);

//Command Struct
typedef struct Command{
    const char *cmd; //!!! should this be the function pointer instead?
    CommandFunc func; //generic pointer to be cast b4 calling
    TokType expected_type;
    int params_size;
}Command;


Command *find_command(const char *cmd);

//FUNCTION IMPLMENTATIONS
int run_cd_impl(const char *path);
void run_echo_impl();
void run_setenv_impl();
void run_unsetenv_impl();
void run_env_impl();
void run_exit_impl();
int run_pwd_impl();
void run_which_impl();

//FUNCTION WRAPPERS
void run_cd_wrapper(int num_tokens, void *args);
void run_echo_wrapper();
void run_setenv_wrapper();
void run_unsetenv_wrapper();
void run_env_wrapper();
void run_exit_wrapper(int num_tokens, void *args);
void run_pwd_wrapper(int num_tokens, void *args);
void run_which_wrapper();














// Command table[] = {
//     {"cd", run_cd},
//     // {"echo", run_echo},
//     // {"setenv", run_setenv},
//     // {"unsetenv", run_unsetenv},
//     // {"env", run_env},
//     // {"exit", run_exit},
//     {"pwd", run_pwd},
//     // {"which", run_which}
// };




// void no_command(const char *com_string);
// int is_builtin(char *string);
// void run_command(const char *cmd);

//     // void malloc_error();
// // int compare_ints(const void *a, const void *b);
// // int find_nl_index(const char *s);
// // char *combine_str_and_free_first(char *s1, char *s2, int len2);
// // void init_my_readline();
// // char *my_readline(int fd);
// // void free_string_array(char **names, int num_names);

#endif