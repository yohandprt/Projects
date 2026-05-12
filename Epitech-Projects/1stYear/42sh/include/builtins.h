/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** builtins.h
*/

#include <stddef.h>

#include "shell.h"

#ifndef BUILTINS_H_
    #define BUILTINS_H_

/* Builtins */
int my_cd(shell_state_t *shell, char **args);
int my_setenv(shell_state_t *shell, char **args);
int my_unsetenv(shell_state_t *shell, char **args);
int my_env(shell_state_t *shell, char **args);
int my_where(shell_state_t *shell, char **args);
int my_which(shell_state_t *shell, char **args);
int my_repeat(shell_state_t *shell, char **args);

static const builtin_t builtin_handler[] = {
    {"cd", &my_cd},
    {"setenv", &my_setenv},
    {"unsetenv", &my_unsetenv},
    {"env", &my_env},
    {"where", &my_where},
    {"which", &my_which},
    {"repeat", &my_repeat},
    {NULL, NULL}
};

#endif
