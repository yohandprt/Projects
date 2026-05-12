/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** globbing_count.c
*/

#include "shell.h"
#include "globbing.h"
#include <stddef.h>


int count_for_arg(char **matches)
{
    int count = 0;

    if (matches) {
        for (int j = 0; matches[j]; j++)
            count++;
        free_tab(matches);
    } else {
        count = 1;
    }
    return count;
}

int count_expanded_args(char **args)
{
    int count = 0;
    char **matches = NULL;

    for (int i = 0; args[i]; i++) {
        if (has_wildcard(args[i])) {
            matches = get_pattern(args[i]);
            count += count_for_arg(matches);
        } else {
            count++;
        }
    }
    return count;
}
