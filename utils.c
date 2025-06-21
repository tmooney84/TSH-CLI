#include "utils.h"

int READLINE_READ_SIZE = 1024;
char *storage = NULL;


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

//!!! JUST FOR INITIAL CONCEPTS
char **parse_string(const char *string, int string_length, int *num_tokens)
{
    *num_tokens = 0;
    int in_word = 0;

    // how many substrings does the string contain
    for (int i = 0; i < string_length && string[i] != '\0'; i++)
    {
        if (string[i] != ' ')
        {
            if (!in_word)
            {
                in_word = 1;
                (*num_tokens)++;
            }
        }
        else
        {
            in_word = 0;
        }
    }

    // create array of empty strings
    char **tokens_list = malloc(*num_tokens * sizeof(char *));
    if (!tokens_list)
    {
        printf("Unable to read input\n");
        return NULL;
    }
    memset(tokens_list, '\0', *num_tokens);

    for (int i = 0; i < *num_tokens; i++)
    {
        tokens_list[i] = malloc((string_length + 1) * (sizeof(char)));
        if (!tokens_list)
        {
            printf("Unable to allocate memory.");
            for (int j = 0; j < i; j++)
            {
                free(tokens_list[j]);
            }
            free(tokens_list);
            return NULL;
        }
        memset(tokens_list[i], '\0', (string_length + 1));
    }

    // tokenize string into sub-strings in token_list
    int ss_idx = 0; // substring index
    in_word = 0;    // flag to indicate that currently iterating through word
    for (int i = 0, j = 0; i < string_length && j < *num_tokens; i++)
    {
        if (string[i] != ' ')
        {
            if (in_word == 0)
            {
                in_word = 1;
            }

            tokens_list[j][ss_idx] = string[i];
            ss_idx++;
        }
        else
        {
            if (in_word == 1)
            {
                j++;
            }
            in_word = 0;
            ss_idx = 0;
        }
    }

    return tokens_list;
}