#include "builtin_cmds.h"

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
    char *string_args; // will need further processing
} WHICH_Args;

// FUNCTION IMPLMENTATIONS
int run_cd_impl(const char *path)
{
    if (path == NULL || strcmp(path, "") == 0 || strcmp(path, "~") == 0)
    {
        const char *home = getenv("HOME");
        if (!home)
        {
            perror("cd: HOME environment variable not set\n");
            return -1;
        }
        if (chdir(home) == 0)
        {
            return 0;
        }
    }
    else if (chdir(path) == 0)
    {
        return 0;
    }
    else
    {
        fprintf(stderr, "cd: no such file or directory: %s", path);
    }
    return -1;
}

void run_echo_impl(char **strings, int num_strings)
{
    if (strings == NULL || strcmp(strings[0], "") == 0)
    {
        printf("\n");
    }
    else
    {
        for (int i = 0; i < num_strings; i++)
        {
            printf("%s\n", strings[i]);
        }
    }
}

void run_env_impl()
{
    /*SIMPLE PRINT VARIABLES IMPLEMENTATION*/
    for (char **env = environ; *env != NULL; env++)
    {
        printf("%s\n", *env);
    }
}

void run_setenv_impl(const char *name, const char *value)
{
    if (name == NULL || name == NULL || strcmp(name, "") || strcmp(value, ""))
    {
        // print out all environmental variables
        run_env_impl();
    }
    else
    {
        if (setenv(name, value, 1) != 0)
        {
            perror("ERROR: run_setenv_impl");
        }
    }
}

void run_unsetenv_impl() {}

void run_exit_impl()
{
    exit(EXIT_SUCCESS);
}

int run_pwd_impl()
{
    char *buf = malloc(BUF_SIZE * sizeof(char));
    if (!buf)
    {
        malloc_error();
        return -1;
    }
    else if (getcwd(buf, BUF_SIZE) == NULL)
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

void run_which_impl() {}

// FUNCTION WRAPPERS
void run_cd_wrapper(int num_tokens, void *args)
{
    if (num_tokens == TOK_CD)
    {
        CD_Args *a = args; // this is really tokens_list[1] bc passed this in
        run_cd_impl(a->name);

        free(a);
        return;
    }
    else if (num_tokens == 1)
    {
        run_cd_impl("");
    }
    else
    {
        perror("Error: invalid path length\n");
        return;
    }
}

void run_echo_wrapper(int num_tokens, void *args)
{
    if (num_tokens >= TOK_ECHO)
    {
        ECHO_Args *a = malloc(sizeof(ECHO_Args));
        if (!a)
        {
            malloc_error();
            return;
        }
        a->strings = args;
        a->num_strings = num_tokens - 1;
        run_echo_impl(a->strings, a->num_strings);

        free(a);
    }
    else if (num_tokens == 1)
    {
        run_echo_impl(args, 0);
    }
    else
    {
        perror("ERROR: run_echo_wrapper\n");
    }
}
void run_export_wrapper(int num_tokens, void *args)
{
    if (num_tokens == TOK_EXPORT)
    {
        EXPORT_Args *a = malloc(sizeof(ECHO_Args));
        // need to parse around = sign
        //parse name and value
        run_setenv_impl()
    }
    else
    {
        perror("ERROR: run_export_wrapper\n");
    }
} //***ADDITIONAL PROCESSING: need to parse the around the = to get the name and value args + need to check int overwrite???

void run_unsetenv_wrapper() {}

void run_env_wrapper(int num_tokens, void *args) {
   //*SIMPLE PRINT VARIABLES IMPLEMENTATION */ 
    if(num_tokens == TOK_ENV){
        run_env_impl();
    }
    else{
        /*WOULD HAVE MORE SOPHISTICATION IN FULL IMPLEMENTATION*/
        run_env_impl();
    }
}

//***can actually have exit status fed into it
void run_exit_wrapper(int num_tokens, void *args)
{
    if (num_tokens == TOK_EXIT && args == NULL)
    {
        run_exit_impl();
    }
}

void run_pwd_wrapper(int num_tokens, void *args)
{
    if (num_tokens == TOK_PWD && strcmp(args, "") == 0)
    {
        run_pwd_impl();
    }
    else
    {
        perror("ERROR: run_pwd_wrapper");
    }
}
void run_which_wrapper() {}

// Command Table
Command table[] = {
    {"cd", run_cd_wrapper, TOK_CD, sizeof(CD_Args)},
    {"echo", run_echo_wrapper, TOK_ECHO, sizeof(ECHO_Args)},
    //{"export", run_export_wrapper, TOK_EXPORT, sizeof(EXPORT_Args)}, // {"setenv", run_setenv},
    //{"unset", run_unsetenv_wrapper, TOK_UNSET, sizeof(UNSET_Args)},
    // {"env", run_env},
    {"exit", run_exit_wrapper, TOK_EXIT, 0},
    {"pwd", run_pwd_wrapper, TOK_PWD, 0}
    // {"which", run_which}
};

void no_command(const char *com_string)
{
    printf("zsh: command not found: %s", com_string);
}

int table_size = sizeof(table) / sizeof(table[0]);

Command *find_command(const char *cmd)
{
    for (int i = 0; i < table_size; i++)
    {
        if (strcmp(cmd, table[i].cmd) == 0)
        {
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

// echo --> print to screen... printf

// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//>echo $USER
// hanna

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

// getenv???

// setenv --> set environment
// export MY_VARIABLE = "my_value"
// need to parse string

// pass entire string through with export keyword and parse so that capture variable until space
// or '=' and then with "" capture what is inside

// int setenv(const char *envname, const char *envval, int overwrite);
//     returns 0/-1

//******** */
// int run_export(const char *var_str){
//     int setenv(env_name, var_str, ???)
// }

// unsetenv --> unsets environment
//     returns 0/-1
// unset MY_VARIABLE
// int unsetenv(const char *name);

// exit --> closes terminal... kill

// pwd --> should be getcwd & printf

// which --> needs to find $PATH location... not sure
// how to build appropriately yet
//  >>> if arg is builtin command: cd: shell built-in command

/*********************************************** */

int bi_main(void)
{
    char *test_input = malloc(255 * sizeof(char));
    if (!test_input)
    {
        printf("Red Alert...Error.");
    }

    // run_pwd_impl();

    // strcpy(test_input, "cd prime");
    // strcpy(test_input, "pwd");
    strcpy(test_input, "exit");

    Tokens_List *list = parse_command(test_input);
    if (!list)
    {
        printf("We got an error here...");
    }

    print_str_array(list->tokens);

    // Check if builtin function with tokens_list[0]
    Command *bif = find_command(list->tokens[0]);
    int check_size = (int)(list->num_tokens - 1) * sizeof(char *);

    // go from tokens_list[1] until end and find size
    if (bif != NULL && (bif->params_size == check_size))
    {
        // execute built-in function
        int num_tokens = list->num_tokens;
        bif->func(num_tokens, &list->tokens[1]);
    }

    // run_pwd_impl();

    printf("Still running!!!");

    return 0;
}
