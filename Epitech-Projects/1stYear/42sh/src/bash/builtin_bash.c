/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** builtin_set.c
*/

#include "bash.h"
#include "shell.h"
#include "alias.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int process_set_arg(shell_state_t *shell, char *arg)
{
    char *equals = strchr(arg, '=');
    int status = 0;
    char *name = NULL;
    char *value = NULL;

    if (equals != NULL) {
        *equals = '\0';
        name = arg;
        value = equals + 1;
        status = set_bash_var(shell->bash_env, name, value);
        *equals = '=';
        if (status != 0)
            return status;
    } else {
        status = set_bash_var(shell->bash_env, arg, "");
        if (status != 0)
            return status;
    }
    return 0;
}

int builtin_set(shell_state_t *shell, char **args)
{
    int i = 1;
    int status = 0;

    if (args[1] == NULL) {
        display_bash_env(shell->bash_env);
        return 0;
    }
    while (args[i] != NULL) {
        status = process_set_arg(shell, args[i]);
        if (status != 0)
            return status;
        i++;
    }
    return 0;
}

int builtin_unset(shell_state_t *shell, char **args)
{
    int i = 1;

    if (args[1] == NULL) {
        fprintf(stderr, "unset: Too few arguments.\n");
        return 1;
    }
    while (args[i] != NULL) {
        unset_bash_var(shell->bash_env, args[i]);
        i++;
    }
    return 0;
}

int handle_bash_command(shell_state_t *shell, char **args)
{
    if (args == NULL || args[0] == NULL)
        return 1;
    if (strcmp(args[0], "set") == 0) {
        shell->last_exit_status = builtin_set(shell, args);
        return 0;
    }
    if (strcmp(args[0], "unset") == 0) {
        shell->last_exit_status = builtin_unset(shell, args);
        return 0;
    }
    if (strcmp(args[0], "alias") == 0) {
        shell->last_exit_status = builtin_alias(shell, args);
        return 0;
    }
    if (strcmp(args[0], "unalias") == 0) {
        shell->last_exit_status = builtin_unalias(shell, args);
        return 0;
    }
    return 1;
}
