/*
** EPITECH PROJECT, 2025
** error_handling.c
** File description:
** error_handling
*/

#include "amazed.h"

char *remove_comment(char *str)
{
    int len = 0;
    char *new_str = NULL;
    int i = 0;

    if (str == NULL)
        return NULL;
    len = my_strlen(str);
    new_str = malloc(len + 1);
    if (!new_str)
        return NULL;
    for (i = 0; i < len; i++) {
        if (str[i] == '#' || str[i] == '\n')
            break;
        new_str[i] = str[i];
    }
    while (i > 0 && new_str[i - 1] == ' ')
        i--;
    new_str[i] = '\0';
    return new_str;
}

graph_t *return_error(graph_t *graph, int display)
{
    if (display)
        output(graph);
    free_graph(graph);
    return NULL;
}
