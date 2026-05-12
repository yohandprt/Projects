/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** wildcard.c
*/

#include "shell.h"
#include "executor.h"
#include <stddef.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <fnmatch.h>
#include <stdio.h>
#include "globbing.h"

char **expand_globbing(char **args)
{
    int new_argc = 0;
    char **new_args = NULL;

    if (!args)
        return args;
    new_argc = count_expanded_args(args);
    if (!has_globbing_change(args))
        return args;
    new_args = build_expanded_args(args, new_argc);
    if (!new_args)
        return args;
    return new_args;
}
