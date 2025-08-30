#include <string.h>

#include "utils.h"

int READLINE_READ_SIZE = 1024;
char *storage = NULL;

void malloc_error()
{
    perror("Unable to allocate memory.\n");
}

int find_nl_index(const char *s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == '\n')
        {
            return i;
        }
        i++;
    }
    return -1;
}

char *combine_str_and_free_first(char *s1, char *s2, int len2)
{
    int len1 = 0;
    if (s1 != NULL)
    {
        len1 = strlen(s1);
    }
    char *result = (char *)malloc(len1 + len2 + 1);
    if (result == NULL)
    {
        return NULL;
    }

    if (s1 != NULL)
    {
        strcpy(result, s1);
        free(s1);
    }
    memcpy(result + len1, s2, len2);
    result[len1 + len2] = '\0';
    return result;
}

void init_my_readline()
{
    if (storage)
    {
        free(storage);
        storage = NULL;
    }
}

char *my_readline(int fd)
{
    char buffer[READLINE_READ_SIZE + 1];
    char *line = NULL;
    ssize_t bytes_read;
    int newline_index = -1;

    if (storage != NULL)
    {
        newline_index = find_nl_index(storage);
        if (newline_index != -1)
        {
            line = strndup(storage, newline_index);
            char *new_storage = strdup(storage + newline_index + 1);
            free(storage);
            storage = new_storage;
            return line;
        }
        else
        {
            line = strdup(storage);
            free(storage);
            storage = NULL;
        }
    }

    while ((bytes_read = read(fd, buffer, READLINE_READ_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        newline_index = find_nl_index(buffer);

        if (newline_index != -1)
        {
            line = combine_str_and_free_first(line, buffer, newline_index);
            storage = strdup(buffer + newline_index + 1);
            return line;
        }
        else
        {
            line = combine_str_and_free_first(line, buffer, bytes_read);
        }
    }

    if (line != NULL && *line != '\0')
    {
        return line;
    }
    if (line != NULL)
    {
        free(line);
    }
    return NULL;
}

void free_string_array(char **names, int num_names)
{
    if (names == NULL)
    {
        return;
    }

    for (int i = 0; i < num_names; i++)
    {
        free(names[i]);
    }

    free(names);
}

void print_str_array(char **str){
    int i = 0; 
    while(str[i] != NULL){
        printf("Token[%d]: %s\n", i, str[i]);
        i++;
    }
    
    return;
}

/*
    Need to account for EXPORT and ECHO 
    ^^^could potentially use conditionals
*/
//char **parse_command(const char *string, int *num_tokens, int *array_size)
Tokens_List *parse_command(char *string)
{
    Tokens_List *list = malloc(sizeof(Tokens_List));
    if(!list){
        malloc_error();
        return NULL;
    }

    int bufsize = TOK_BUFSIZE;
    int pos = 0;
    list->tokens = malloc(bufsize * sizeof(char *));
    if(!list->tokens){
        malloc_error();
        exit(EXIT_FAILURE);
    }

    char *token;
    char *s_tok;

    token = strtok_r(string, TOK_DELIM, &s_tok);

    while(token != NULL){
        list->tokens[pos] = token; 
        pos++;

        if(pos >= bufsize){
            bufsize += TOK_BUFSIZE;
            list->tokens = realloc(list->tokens, bufsize *sizeof(char*));
            if(!list->tokens){
                malloc_error();
                exit(EXIT_FAILURE);
            }
        }
        token = strtok_r(NULL, TOK_DELIM, &s_tok);
    }
    list->num_tokens = pos;
    list->array_size = bufsize;

    list->tokens[pos] = NULL;  //creates a null terminated array
    
    return list;
}