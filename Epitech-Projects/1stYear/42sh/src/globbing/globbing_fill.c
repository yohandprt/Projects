/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** globbing_fill.c
*/

#include "shell.h"
#include "globbing.h"
#include <string.h>
#include <stdlib.h>

int fill_for_arg(char **array, const char *arg, char **new_args, int k)
{
    if (array) {
        for (int j = 0; array[j]; j++) {
            new_args[k] = strdup(array[j]);
            k++;
        }
        free_tab(array);
    } else {
        new_args[k] = strdup(arg);
        k++;
    }
    return k;
}

void fill_expanded_args(char **args, char **new_args)
{
    int k = 0;
    char **array = NULL;

    for (int i = 0; args[i]; i++) {
        if (has_wildcard(args[i])) {
            array = get_pattern(args[i]);
            k = fill_for_arg(array, args[i], new_args, k);
        } else {
            new_args[k] = strdup(args[i]);
            k++;
        }
    }
    new_args[k] = NULL;
}

char **build_expanded_args(char **args, int new_argc)
{
    char **new_args = malloc(sizeof(char *) * (new_argc + 1));

    if (!new_args)
        return NULL;
    fill_expanded_args(args, new_args);
    return new_args;
}
