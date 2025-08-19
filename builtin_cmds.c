#include "builtin_cmds.h"
#include "utils.h"

// #ifndef UTILS_H
// #define UTILS_H

// #include <stdlib.h>
// #include <fcntl.h>
// #include <sys/stat.h>

#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 255
#define MAX_STR_LEN 255

//ARG CONVERSION STRUCTS
typedef struct {
    char name [MAX_STR_LEN];
}CD_Args;

typedef struct {
    char string [MAX_STR_LEN];
}ECHO_Args;

typedef struct {
    char name [MAX_STR_LEN];
    char value [MAX_STR_LEN];
    int overwrite;
}SETENV_Args;

typedef struct {
    char name [MAX_STR_LEN];
}UNSETENV_Args;

typedef struct {
    char string_args [MAX_STR_LEN]; //will need further processing
}WHICH_Args;


//check if string is in built-in function
int is_builtin(char *string){
    
}


void run_command(const char *cmd){
    
}

void no_command(const char *com_string){
    printf("zsh: command not found: %s", com_string);
}



//FUNCTION IMPLMENTATIONS
int run_cd_impl(const char *path){
    const char* home_dir = getenv("HOME");
    if(path == "" || path == " "){
        if(chdir(path) == 0)
        {
            return 0;
        }
    }
    else if(chdir(path) == 0){
        return 0;
    }
    else{
        fprintf(stderr,"cd: no such file or directory: %s", path);
    }
    return -1;
}

void run_echo_impl(){}
void run_setenv_impl(){}
void run_unsetenv_impl(){}
void run_env_impl(){}
void run_exit_impl(){}

int run_pwd_impl(){
    char *buf = malloc(BUF_SIZE* sizeof(char));
    if(!buf){
        malloc_error();
        return -1;
    }
    else if(getcwd(buf, BUF_SIZE) == NULL)
    {
        perror("getcwd failed");
        free(buf);
        buf = NULL;
        return -1;
    }
    printf("%s\n", buf);
    free(buf);
    buf = NULL;
    return 0;
}

void run_which_impl(){}



//FUNCTION WRAPPERS
void run_cd_wrapper(void *args){
    if(sizeof(args) < MAX_STR_LEN){
        CD_Args *a = args;
        run_cd_impl(a->name);
        return;
    }
    else{
        perror("Error: invalid path length\n");
        return;
    }
}

void run_echo_wrapper(){}
void run_setenv_wrapper(){}
void run_unsetenv_wrapper(){}
void run_env_wrapper(){}
void run_exit_wrapper(){}
void run_pwd_wrapper(){}
void run_which_wrapper(){}


typedef enum{
    ARG_CD = 2,
    ARG_ECHO = 2,
    ARG_SETENV = 4,
    ARG_UNSETENV = 2,
    ARG_ENV = 1,
    ARG_EXIT = 1, 
    ARG_PWD = 1,
    ARG_WHICH = 2 //>>>needs to be variable... args until null... maybe parse char * pointers until then
} ArgType;

//Command Struct
typedef struct Command{
    const char *cmd; //!!! should this be the function pointer instead?
    void *func; //generic pointer to be cast b4 calling
    ArgType expected_type;
    size_t arg_size;
}Command;


//Command Table
Command table[] = {
    {"cd", run_cd_wrapper, ARG_CD, sizeof(CD_Args)},
    // {"echo", run_echo},
    // {"setenv", run_setenv},
    // {"unsetenv", run_unsetenv},
    // {"env", run_env},
    // {"exit", run_exit},
    {"pwd", run_pwd_wrapper, ARG_PWD, 0},
    // {"which", run_which}
};

void no_command(const char *com_string);
int is_builtin(char *string);
void run_command(const char *cmd);

Command* find_command(const char *cmd){
for(size_t i = 0; i < sizeof(table)/sizeof(table[0]); i++){
    if(strcmp(cmd, table[i].cmd) == 0){
        return &table[i];
    }
}
    return NULL;
}

    // void malloc_error();
// int compare_ints(const void *a, const void *b);
// int find_nl_index(const char *s);
// char *combine_str_and_free_first(char *s1, char *s2, int len2);
// void init_my_readline();
// char *my_readline(int fd);
// void free_string_array(char **names, int num_names);

// #endif






//echo --> print to screen... printf

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//>echo $USER 
//hanna

// void run_echo(const char *string)
//    {
//         printf("%s\n", string);
//     } 


/*
env --> prints environment
echo $HOME ...
if echo and $ then pass in HOME


int env(const char *var_str){
    if
}

*/








//getenv???

//setenv --> set environment
//export MY_VARIABLE = "my_value"
//need to parse string

//pass entire string through with export keyword and parse so that capture variable until space 
//or '=' and then with "" capture what is inside


//int setenv(const char *envname, const char *envval, int overwrite);
//    returns 0/-1

//******** */
// int run_export(const char *var_str){
//     int setenv(env_name, var_str, ???)
// }


//unsetenv --> unsets environment
//    returns 0/-1
//unset MY_VARIABLE
//int unsetenv(const char *name);





//exit --> closes terminal... kill

//pwd --> should be getcwd & printf

//which --> needs to find $PATH location... not sure
//how to build appropriately yet
// >>> if arg is builtin command: cd: shell built-in command


