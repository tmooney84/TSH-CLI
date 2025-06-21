#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main(void){
/*LOOP
while(quit_flag != 0)
{
    char * cwd = get_cwd();
    printf("[TSH: %s]>", cwd);
    fflush(stdout);

    //Read: Read the command line from standard input

    char *input_string = my_readline(0);
    if (input_string == NULL)
    {
        quit_flag = 1; >>> may be useful if broken
        free(input_string);
        break;  
    }
    else if (strcmp(input_string, "") == 0 || strcmp(input_string, " ") == 0)
    {
        free(input_string);
        continue;
    }
    
    int num_tokens = 0;
    
    
    //Parse: Separate the command string into a program and arguments (Lexer - AST???)
        // >>> if single token that is equal to exit >>> make sure to exit;; may require kill processing of TSH shell
        //>>> if single token, check if what is typed into the prompt is a folder name, cd to that folder ;; this will match zsh
        // else separate into program and arguments... don't need to worry about pipes and redirection, so do I need AST?
        

    //will need & to access in called function
    char **tokens_list = parse_string/lexer-ast(input_string, INPUT_STRING_LENGTH, &num_tokens)?
    if (!tokens_list)
    {
        error_message?();
        free(input_string);
        continue; ??? 
    }


    //Execute: Run the parsed command >>> differentiate process creation with binary and built-in commands






    cleanup: freeing string array, input_string
}


    TSH:cwd ==>command readline  (TSH format)
        Read: Read the command from standard input
            use my_readline logic to capture string up until \n. parse and execute 
            in loop and if additional strings will run again... may need a flag or
            check if anything in the storage buffer,
        Parse: Separate the command string into a program and arguments
            Lexer - AST?

        Execute: Run the parsed command


    *** need the readline logic to take in multiple
    '\n''s so that you could copy in a long command
    into the cli or at least give the opportunity
    to do that
*/


//type_prompt();
//read_command(command, parameter);



// if (is_builtin(command)) {
//     handle_builtin(command, args);
// } else {
//     pid_t pid = fork();
//     if (pid == 0) {
//         // child process
//         execvp(command, args);
//         perror("exec failed");
//         exit(EXIT_FAILURE);
//     } else {
//         // parent process
//         waitpid(pid, NULL, 0);
//     }
// }
// }

    return 0;
}