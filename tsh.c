#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#include "builtin_cmds.h"
#include "utils.h"

char *get_cwd()
{
    char *buf = malloc(BUF_SIZE * sizeof(char));
    if (!buf)
    {
        malloc_error();
        return NULL;
    }
    char *wd = getcwd(buf, BUF_SIZE);

    int wd_size = strlen(wd);

    char *rel_wd = malloc((wd_size + 1) * sizeof(char));
    if (!rel_wd)
    {
        malloc_error();
        return NULL;
    }

    for (int i = wd_size - 1; i >= 0; i--)
    {
        if (wd[i] == '/')
        {
            int len = wd_size - (i - 1) + 1;
            snprintf(rel_wd, len, "%s", wd + (i + 1));
            break;
        }
    }
    return rel_wd;
}

int launch_command(char **args)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0)
    {
        // Child Process
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);

        if (execvp(args[0], args))
        {
            perror("tsh");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        // Error forking
        perror("tsh");
    }
    else
    {
        // Parent process
        do
        {
          waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int main(void)
{
    signal(SIGINT, SIG_IGN);   // Ignore Ctrl+C in shell
    signal(SIGTSTP, SIG_IGN);  // Ignore Ctrl+Z in shell

    // LOOP
    while (1)
    {
        char *cwd = get_cwd(); // get current working directory*********
        printf("[TSH: %s]> ", cwd);
        fflush(stdout);

        // Read: Read the command line from standard input
        char *input_string = my_readline(0);
        if (input_string == NULL)
        {
            free(input_string);
            continue;
        }
        else if (strcmp(input_string, "") == 0 || strcmp(input_string, " ") == 0)
        {
            free(input_string);
            continue;
        }

        Tokens_List *list = parse_command(input_string);
        if (!list)
        {
            perror("Unable to build Tokens List\n");
            free(cwd);
            cwd = NULL;
            free(input_string);
            input_string = NULL;
            return EXIT_FAILURE;
        }

        if(strcmp(list->tokens[0], "exit") == 0){
            break;
        }

        Command *bif = find_command(list->tokens[0]);
        if (bif != NULL)
        {
            // execute built-in function
            bif->func(list->num_tokens, &list->tokens[1]);
        }

        //Run non-builtin cmds
        else
        {
            launch_command(list->tokens);
        }
        
        //Set pointer to .data to NULL
        free(list);
        list = NULL;

        //Set pointer to .data to NULL
        bif = NULL;

        free(cwd);
        cwd = NULL;
    }
    
    return 0;
}
