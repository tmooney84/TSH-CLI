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

// ARG CONVERSION STRUCTS
typedef struct
{
    char *name;
} CD_Args;

typedef struct
{
    char **strings;
    int num_strings;
} ECHO_Args;

typedef struct
{
    char *name;
    char *value;
    // int overwrite; //>>> will need to atoi to have int
} EXPORT_Args;

typedef struct
{
    char *name;
} UNSET_Args;

typedef struct
{
    char **string_args; // will need further processing
} WHICH_Args;


typedef void (*CommandFunc)(int, void *);

typedef enum{
    TOK_CD = 2,
    TOK_ECHO = 2,
    TOK_EXPORT = 2,  
    TOK_UNSET = 2,   
    TOK_ENV = 1,
    TOK_EXIT = 1, 
    TOK_PWD = 1,
    TOK_WHICH = 2 
} TokType;

typedef void (*CommandFunc)(int, void *);

//Command Struct
typedef struct Command{
    const char *cmd; 
    CommandFunc func; 
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

#endif