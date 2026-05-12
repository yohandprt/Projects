/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** globbing_check.c
*/

#include "shell.h"
#include "globbing.h"
#include <string.h>

int verif_actually_files(const char *arg)
{
    char **matches = get_pattern(arg);
    int expanded = 0;

    if (matches && matches[0] &&
        !(matches[1] == NULL && strcmp(matches[0], arg) == 0))
        expanded = 1;
    free_tab(matches);
    return expanded;
}

static int has_globbing_in_args(char **args)
{
    for (int i = 0; args[i]; i++) {
        if (has_wildcard(args[i]) && verif_actually_files(args[i]))
            return 1;
    }
    return 0;
}

int has_globbing_change(char **args)
{
    int new_argc = count_expanded_args(args);
    int old_argc = 0;

    for (; args[old_argc]; old_argc++);
    if (new_argc == old_argc) {
        if (!has_globbing_in_args(args))
            return 0;
    }
    return 1;
}
