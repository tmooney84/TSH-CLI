#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#include "builtin_cmds.h"
#include "utils.h"

// int count_tokens(char *string, int string_len)
// {
//     int num_tokens = 0;
//     int in_word = 0;

//     for (int i = 0; i < string_len && string[i] != '\0'; i++)
//     {
//         if (string[i] != ' ')
//         {
//             if (!in_word)
//             {
//                 in_word = 1;
//                 num_tokens++;
//             }
//         }
//         else
//         {
//             in_word = 0;
//         }
//     }
//     return num_tokens;
// }

// void init_token_list(Token_List *list)
// {
//     list->tokens = NULL;
//     list->num_tokens = 0;
// }

// Token_List *build_token_list(char *input_string, int string_len, int num_tokens)
// {
//     Token_List *list = malloc(sizeof(Token_List));
//     if (!list)
//     {
//         malloc_error();
//         //!!! need to free stuff???
//         return NULL;
//     }
//     void init_token_list(Token_List * list);

//     list->tokens = malloc(sizeof(Lex_Token *));
//     list->num_tokens = num_tokens;

//     for (int i = 0; i < list->num_tokens; i++)
//     {
//         list->tokens[i] = malloc(sizeof(Lex_Token));
//         if (list->tokens[i])
//         {
//             malloc_error();
//             //!!! need to free stuff???
//             return NULL;
//         }

//         list->tokens[i]->tok_str = malloc(MAX_TOKEN_SIZE * sizeof(char));
//         if (list->tokens[i]->tok_str)
//         {
//             malloc_error();
//             //!!! need to free stuff???
//             return NULL;
//         }
//         memset(list->tokens[i]->tok_str, 0, MAX_TOKEN_SIZE);

//         list->tokens[i]->lex_type = UNKNOWN;
//         list->tokens[i]->tok_len = 0;
//     }

//     return list;
// }

// void tokenize_input(char *string, int string_len, Token_List *list, int num_tokens)
// {
//     // tokenize string into sub-strings in token_list
//     int ss_idx = 0;  // substring index
//     int in_word = 0; // flag to indicate that currently iterating through word
//     for (int i = 0, j = 0; i < string_len && j < num_tokens; i++)
//     {
//         if (string[i] != ' ')
//         {
//             if (in_word == 0)
//             {
//                 in_word = 1;
//             }

//             list->tokens[j]->tok_str[ss_idx] = string[i];
//             ss_idx++;
//         }
//         else
//         {
//             list->tokens[j]->tok_len = ss_idx; //****test to make sure */
//             if (in_word == 1)
//             {
//                 j++;
//             }
//             in_word = 0;
//             ss_idx = 0;
//         }
//     }
//     return list;
// }

// enum Type classify_tok(char *tok, int tok_len, int tok_num)
// {
//     // UNKNOWN = 0
//     if (tok == NULL)
//     {
//         return UNKNOWN;
//     }

//     // PROG
//     if (tok_num == 0 && ((tok[0] >= 'A' && tok[0] <= 'Z') || (tok[0] >= 'a' && tok[0] <= 'z')))
//     {
//         return PROG;
//     }

//     // EXE
//     else if (tok_num == 0 && (tok[0] == '.' && tok[1] == '/'))
//     {
//         return EXE;
//     }

//     // FLAG_ARG
//     else if (tok_num > 1 && tok[0] == '-')
//     {
//         return FLAG_ARG;
//     }

//     // REG_ARG
//     else if (tok_num > 1 && tok[0] != '-' && tok[0] != '"')
//     {
//         return REG_ARG;
//     }

//     // STR_ARG
//     else if (tok_num > 1 && tok[0] == '"' && tok[tok_len - 1] == '"')
//     {
//         return REG_ARG;
//     }

//     return UNKNOWN;
// }

// void classify_lex_toks(Token_List *list, int num_tokens)
// {
//     for (int i = 0; i < num_tokens; i++)
//     {
//         list->tokens[i]->lex_type = classify_tok(list->tokens[i]->tok_str, list->tokens[i]->tok_len, i);
//     }
// }

// Token_List *parse_command(const char *string, int string_len)
// {
//     int num_tokens = count_tokens(string, string_len);
//     Token_List *list = build_token_list(string, string_len, num_tokens);
//     if (!list)
//     {
//         malloc_error();
//         ///!!! Make sure the stuff in build_token_list???
//         return NULL;
//     }
//     tokenize_input(string, string_len, list, num_tokens);
//     classify_lex_toks(list, num_tokens);

//     return list;
// }

char *get_cwd(){
    char *buf = malloc(BUF_SIZE * sizeof(char));
    if(!buf){
        malloc_error();
        return NULL;
    }
    char *wd = getcwd(buf, BUF_SIZE);
    
    int wd_size = strlen(wd);

    char *rel_wd = malloc((wd_size + 1) * sizeof(char));
    if(!rel_wd){
        malloc_error();
        return NULL;
    }

    for(int i = wd_size - 1; i >= 0; i--){
        if(wd[i] == '/'){
            int len = wd_size - (i-1) + 1;  
            snprintf(rel_wd, len, "%s", wd + (i+1));
            break;
        }
    }
    return rel_wd;
}


int main(void)
{
    //build lookup table >>> this is better done at compile time
   // static B_Table *b_lookup_table = {NULL};
   // b_lookup_table = build_b_table(b_lookup_table);

    int quit_flag;

    //LOOP
    while(quit_flag != 0)
    {
        char *cwd = get_cwd();   //get current working directory*********
        printf("[TSH: %s]>", cwd);
        fflush(stdout);

        //Read: Read the command line from standard input

        char *input_string = my_readline(0);
        if (input_string == NULL)
        {
            quit_flag = 1; //>>> may be useful if broken
            free(input_string);
            break;
        }
        else if (strcmp(input_string, "") == 0 || strcmp(input_string, " ") == 0)
        {
            free(input_string);
            continue;
        }

        //do I need this???
        int string_len = strlen(input_string);

        //Parse: Separate the command string into a program and arguments (Lexer - AST???)

            // ./ >>> at beginning of token means execute following executable file (error)>>> tsh: persmission denied: ./file1.txt
            // >>> if single token that is equal to exit >>> make sure to exit;; may require kill processing of TSH shell
            //>>> if single token, check if what is typed into the prompt is a folder name, cd to that folder ;; this will match zsh
            
            //***with that single folder name check it after checking through the commands list, then 
        //    can do the error:
        //    zsh: command not found: adsf
            
            // else separate into program and arguments... don't need to worry about pipes and redirection, so do I need AST?

        //parse_input

        int num_tokens;
        int array_size;

        /*
        NEED TO UPDATE TO STRUCTURE FORMAT!!! start on line 256
        */
        //char **tokens_list = parse_command(input_string, &num_tokens, &array_size);
        Tokens_List *list = parse_command(input_string);
        if(!list)
        {
            perror("Unable to build Tokens List\n");
            free(cwd);
            cwd = NULL;
            free(input_string);
            input_string = NULL;
            return EXIT_FAILURE;
        }

        //Check if builtin function with tokens_list[0]
        Command *bif = find_command(list->tokens[0]);
        //go from tokens_list[1] until end and find size
        if(bif != NULL && (bif->params_size == (list->num_tokens - 1) * sizeof(char *)))
        {
            //execute built-in function
            bif->func(list->num_tokens, &list->tokens[1]);
        }

        //run non-built-in commands!!!
        else{

        }




        /*
        Need to create at struct to reflect  
        free_string_array(, TOK_BUFSIZE)

        */
        free(cwd);
        cwd = NULL;
    }


            }


        //will need & to access in called function


        //Execute: Run the parsed command >>> differentiate process creation with binary and built-in commands

        //*** CHECK FOR BUILTIN COMMANDS FIRST

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

    // type_prompt();
    // read_command(command, parameter);

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
