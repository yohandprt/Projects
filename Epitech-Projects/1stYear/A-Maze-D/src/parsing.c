/*
** EPITECH PROJECT, 2025
** parsing.c
** File description:
** parsing
*/

#include "amazed.h"

int is_num(char *str)
{
    char *new_str = NULL;

    if (!str)
        return 0;
    new_str = remove_comment(str);
    for (int i = 0; new_str[i] != '\0'; i++) {
        if (!((new_str[i] >= '0' && new_str[i] <= '9') ||
            new_str[i] == '\n')) {
            free(new_str);
            return 0;
        }
    }
    free(new_str);
    return 1;
}

int is_room(char *line)
{
    char **numbers = NULL;
    char *new_line = NULL;

    if (!line)
        return 0;
    new_line = remove_comment(line);
    numbers = str_array_deli(new_line, " ");
    if (!numbers)
        return free_and_return(NULL, new_line, 0);
    if (my_arraylen(numbers) != 3)
        return free_and_return(numbers, new_line, 0);
    for (int i = 0; numbers[i]; i++) {
        if (!is_num(numbers[i]))
            return free_and_return(numbers, new_line, 0);
    }
    return free_and_return(numbers, new_line, 1);
}

int is_tunnel(char *line)
{
    char **numbers = NULL;
    char *new_line = NULL;

    if (!line)
        return 0;
    new_line = remove_comment(line);
    numbers = str_array_deli(new_line, "-");
    if (!numbers)
        return free_and_return(NULL, new_line, 0);
    if (my_arraylen(numbers) != 2)
        return free_and_return(numbers, new_line, 0);
    for (int i = 0; numbers[i]; i++) {
        if (!is_num(numbers[i]))
            return free_and_return(numbers, new_line, 0);
    }
    return free_and_return(numbers, new_line, 1);
}

int verif_file(graph_t *graph, char **lines, int start, int end)
{
    for (int i = 0; lines[i]; i++) {
        if (my_strcmp(lines[i], "##start") == 0
            && lines[i + 1] && is_room(lines[i + 1]))
            start++;
        if (my_strcmp(lines[i], "##end") == 0
            && lines[i + 1] && is_room(lines[i + 1]))
            end++;
    }
    if (start > 1 || end > 1)
        return 84;
    if (start && end)
        return 1;
    if (!start)
        graph->parse->no_start = 1;
    if (!end)
        graph->parse->no_end = 1;
    return 0;
}

int verif_title(char *line)
{
    if (my_strcmp(line, "##start") == 0)
        return 0;
    if (my_strcmp(line, "##end") == 0)
        return 0;
    return 1;
}
