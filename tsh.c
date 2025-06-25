#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#define MAX_TOKEN_SIZE 255

enum Type
{
    UNKNOWN = 0,
    PROG,
    FLAG_ARG,
    STRING_ARG,
    EXE
};

typedef struct lex_token
{
    enum Type lex_type;
    char *tok_str;
    int tok_len;
} Lex_Token;

typedef struct token_list
{
    Lex_Token **tokens;
    int num_tokens;
} Token_List;

int count_tokens(char *string, int string_len)
{
    int num_tokens = 0;
    int in_word = 0;

    for (int i = 0; i < string_len && string[i] != '\0'; i++)
    {
        if (string[i] != ' ')
        {
            if (!in_word)
            {
                in_word = 1;
                num_tokens++;
            }
        }
        else
        {
            in_word = 0;
        }
    }
    return num_tokens;
}

void init_token_list(Token_List *list)
{
    list->tokens = NULL;
    list->num_tokens = 0;
}

Token_List *build_token_list(char *input_string, int string_len, int num_tokens)
{
    Token_List *list = malloc(sizeof(Token_List));
    if (!list)
    {
        malloc_error();
        //!!! need to free stuff???
        return NULL;
    }
    void init_token_list(Token_List * list);

    list->tokens = malloc(sizeof(Lex_Token *));
    list->num_tokens = num_tokens;

    for (int i = 0; i < list->num_tokens; i++)
    {
        list->tokens[i] = malloc(sizeof(Lex_Token));
        if (list->tokens[i])
        {
            malloc_error();
            //!!! need to free stuff???
            return NULL;
        }

        list->tokens[i]->tok_str = malloc(MAX_TOKEN_SIZE * sizeof(char));
        if (list->tokens[i]->tok_str)
        {
            malloc_error();
            //!!! need to free stuff???
            return NULL;
        }
        memset(list->tokens[i]->tok_str, 0, MAX_TOKEN_SIZE);

        list->tokens[i]->lex_type = UNKNOWN;
        list->tokens[i]->tok_len = 0;
    }

    return list;
}

void tokenize_input(char *string, int string_len, Token_List *list, int num_tokens)
{
    // tokenize string into sub-strings in token_list
    int ss_idx = 0;  // substring index
    int in_word = 0; // flag to indicate that currently iterating through word
    for (int i = 0, j = 0; i < string_len && j < num_tokens; i++)
    {
        if (string[i] != ' ')
        {
            if (in_word == 0)
            {
                in_word = 1;
            }

            list->tokens[j]->tok_str[ss_idx] = string[i];
            ss_idx++;
        }
        else
        {
            list->tokens[j]->tok_len = ss_idx; //****test to make sure */
            if (in_word == 1)
            {
                j++;
            }
            in_word = 0;
            ss_idx = 0;
        }
    }
    return list;
}

int main(void)
{
    /*LOOP
    while(quit_flag != 0)
    {
        char *cwd = get_cwd();   //get current working directory*********
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


        //Parse: Separate the command string into a program and arguments (Lexer - AST???)

            // ./ >>> at beginning of token means execute following executable file (error)>>> tsh: persmission denied: ./file1.txt
            // >>> if single token that is equal to exit >>> make sure to exit;; may require kill processing of TSH shell
            //>>> if single token, check if what is typed into the prompt is a folder name, cd to that folder ;; this will match zsh
            // else separate into program and arguments... don't need to worry about pipes and redirection, so do I need AST?

    //parse_input
    //????????Token_List *parse_command(const char *string, int string_length, int num_tokens)
    parse_input::could encapsulate this entire section below

        int string_len = strlen(string);
        
        int num_tokens = count_tokens(char *string, int string_len);

        Token_List *input_toks = build_token_list(input_string, string_len, num_tokens);

        tokenize_input(input_string, string_len, list, num_tokens);

        if(classify_lex_toks(list, num_tokens) != 0)
        {

        }

        //int classify_lex_toks(Token_List *list, int num_tokens)
        {
            for(int i = 0; i < num_tokens; i++)
            {
                list->tokens[i]->lex_type = classify_tok(list->tokens[i]->tok_str, tok_len, i);
            }
        }



        }
                enum Type classify_tok(char *tok, int tok_len, int tok_num)
                {
                    //UNKNOWN = 0
                    
                    //PROG
                    if(tok_num == 0 && ((tok[0] >= 'A' && tok[0] <= 'Z') || (tok[0] >= 'a' && tok[0] <= 'z')))
                    {
                        return PROG; 
                    }
                    
                    //FLAG_ARG

                    //STRING_ARG

                    //EXE
                
                    return UNKNOWN;
                }

enum Type
{
    UNKNOWN = 0,
    PROG,
    FLAG_ARG,
    STRING_ARG,
    EXE
};






        char **parse_command(char *input_string)
        {
            //tokenize_string(input_string);


            //
            // -flag arg

            // ./name_of_cmd -arg -arg "dsfdssda"


            // -string arg
            // program




            }


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