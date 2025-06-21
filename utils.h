#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h> 

int compare_ints(const void *a, const void *b);
int find_nl_index(const char *s);
char *combine_str_and_free_first(char *s1, char *s2, int len2);
void init_my_readline();
char *my_readline(int fd);
char **parse_string(const char *string, int string_length, int *num_tokens);
void free_string_array(char **names, int num_names);

#endif