/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** globbing.h
*/

#ifndef GLOBBING_H
    #define GLOBBING_H
    #include "shell.h"
    #include <dirent.h>

// utils
int has_wildcard(const char *str);
void free_tab(char **tab);
int count_matches(const char *pattern);
char **fill_matches(DIR *dir, const char *pattern, int count);
char **get_pattern(const char *pattern);

// Count
int count_for_arg(char **matches);
int count_expanded_args(char **args);

// Fill
int fill_for_arg(char **matches, const char *arg, char **new_args, int k);
void fill_expanded_args(char **args, char **new_args);
char **build_expanded_args(char **args, int new_argc);

int has_globbing_change(char **args);
char **expand_globbing(char **args);

#endif /* GLOBBING_H */
