#ifndef UTILS_H
#define UTILS_H

#define TOK_BUFSIZE 255
#define TOK_DELIM " \t\r\n\a"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h> 

#define MAX_TOKEN_SIZE 255

typedef struct 
{
    char **tokens;
    int num_tokens;
    int array_size;
}Tokens_List;

Tokens_List *parse_command(char *string);
void print_str_array(char **str);

void malloc_error();
int compare_ints(const void *a, const void *b);
int find_nl_index(const char *s);
char *s_f_combine(char *s1, char *s2, int len2);
void init_my_readline();
char *my_readline(int fd);
void free_string_array(char **names, int num_names);

#endif