#include "builtin_cmds.h"
#include "utils.h"

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

void find_executable(const char *cmd_name){
   char *path_env = getenv("PATH");
   if(!path_env){
        perror("Error: PATH environmental variable not found.\n");
        return;
   }

   char path_copy[MAX_PATH_LEN];
   snprintf(path_copy, MAX_PATH_LEN, "%s", path_env);

   char *dir = strtok(path_copy, ":");
   int found = 0;

   while(dir != NULL){
    char full_path[MAX_PATH_LEN];
    snprintf(full_path, MAX_PATH_LEN, "%s/%s", dir, cmd_name);
   
        if(access(full_path, X_OK) == 0){
            printf("%s\n", full_path);
            found = 1;
            break;
        }

        dir = strtok(NULL, ":");
    }

    if(!found){
        fprintf(stderr, "%s not found\n", cmd_name);
    }

    dir = NULL;
    return;
}

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
        int first_flag = 0;
        int last_flag = 0;
        
        int last_len = strlen(strings[num_strings - 1]);
        
        if(strings[0][0] == '"' && strings[num_strings - 1][last_len - 1] == '"'){
                first_flag = 1; 
                last_flag = 1;
            }
        //need to remove quotes and print on same line with space in between words
        for (int i = 0; i < num_strings; i++)
        {
            if( first_flag && i == 0)
            {
                printf("%s", strings[0] + 1);
            }
            else if(last_flag && i == num_strings - 1)
            {
                printf("%.*s\n", last_len - 1, strings[i]);
            }
            else
                printf("%s", strings[i]);

            if(i != num_strings -1)
            {
                printf(" ");
            }
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
    /*SIMPLE IMPLEMENTATION...MORE SOPHISTICATED PARSING NEEDED FOR FULL VERSION*/
    if (setenv(name, value, 1) != 0)
    {
        perror("ERROR: run_setenv_impl\n");
    }
}

void run_unsetenv_impl(const char *name)
{
    if (unsetenv(name) != 0)
    {
        perror("ERROR: run_unsetenv_impl\n");
    }
}

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

void run_which_impl(int num_args, char **env_vars)
{
    for (int i = 0; i < num_args; i++)
    {
        find_executable(env_vars[i]);
    }

    return;
}

// FUNCTION WRAPPERS
void run_cd_wrapper(int num_tokens, void *args)
{
    if (num_tokens == TOK_CD)
    {
        CD_Args *a = args; // this is really tokens_list[1] bc passed this in
        if (!a)
        {
            malloc_error();
            return;
        }
        run_cd_impl(a->name);

        a = NULL;
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

    return;
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
        a = NULL;
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
        if (!a)
        {
            malloc_error();
            return;
        }

        char **exp_args = (char **)args;

        char *s_tok;
        a->name = strtok_r(exp_args[0], "=", &s_tok);
        a->value = strtok_r(NULL, "=", &s_tok);

        run_setenv_impl(a->name, a->value);

        s_tok = NULL;
        exp_args = NULL;
        free(a);
        a = NULL;
    }
    else if (num_tokens == 1)
    {
        run_env_impl();
    }
    else
    {
        perror("ERROR: run_export_wrapper\n");
    }

    return;
}

void run_unsetenv_wrapper(int num_tokens, void *args)
{
    if (num_tokens == TOK_UNSET)
    {
        UNSET_Args *a = malloc(sizeof(UNSET_Args));
        if (!a)
        {
            malloc_error();
            return;
        }
        char **unset_args = (char **)args;
        a->name = unset_args[0];
        run_unsetenv_impl(a->name);
        unset_args = NULL;

        free(a);
        a = NULL;
    }

    return;
}

void run_env_wrapper(int num_tokens, void *args)
{
    //*SIMPLE PRINT VARIABLES IMPLEMENTATION */
    (void)args;

    // if (num_tokens == TOK_ENV && (strcmp(arr_args[0], "") || arr_args[0] == NULL))
    if (num_tokens == TOK_ENV)
    {
        run_env_impl();
    }
    else
    {
        /*WOULD HAVE MORE SOPHISTICATION IN FULL IMPLEMENTATION*/
        run_env_impl();
    }

    return;
}

//***can actually have exit status fed into it
void run_exit_wrapper(int num_tokens, void *args)
{
    if (num_tokens == TOK_EXIT && args == NULL)
    {
        run_exit_impl();
    }

    return;
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

    return;
}
void run_which_wrapper(int num_tokens, void *args)
{
    if (num_tokens >= TOK_WHICH && args != NULL)
    {
        WHICH_Args *a = malloc(sizeof(WHICH_Args));
        if (!a)
        {
            malloc_error();
            return;
        }
        char **input_args = (char **)args;
        a->string_args = input_args;
        int num_args = num_tokens - 1;
        run_which_impl(num_args, input_args);
        
        input_args = NULL;
        free(a);
        a = NULL;
    }
    else if(num_tokens == 1){
        return;
    }

    else
        {
            perror("ERROR: run_which_wrapper");
        }

    return;
}

// Command Table
Command table[] = {
    {"cd", run_cd_wrapper, TOK_CD, sizeof(CD_Args)},
    {"echo", run_echo_wrapper, TOK_ECHO, sizeof(ECHO_Args)},
    {"export", run_export_wrapper, TOK_EXPORT, sizeof(EXPORT_Args)}, // {"setenv", run_setenv},
    {"unset", run_unsetenv_wrapper, TOK_UNSET, sizeof(UNSET_Args)},
    {"env", run_env_wrapper, TOK_ENV, 0},
    {"exit", run_exit_wrapper, TOK_EXIT, 0},
    {"pwd", run_pwd_wrapper, TOK_PWD, 0},
    {"which", run_which_wrapper, TOK_WHICH, sizeof(WHICH_Args)}};

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

