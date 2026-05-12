/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** builtin_alias.c
*/

#include "alias.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int alias(alias_t *alias, char *args)
{
    char **array = my_str_to_word_array(args, "=\n");
    int result = 0;

    if (my_arraylen(array) != 2) {
        free_array(array);
        return 84;
    }
    result = add_alias(&alias, array[0], array[1]);
    free_array(array);
    return result;
}

void print_alias(alias_t *alias)
{
    alias_t *current = alias;

    if (!current)
        return;
    for (; current != NULL; current = current->next) {
        if (current->attribute && current->new_attribute) {
            printf("%s=%s\n", current->attribute,
                current->new_attribute);
        }
    }
}

int builtin_unalias(shell_state_t *shell, char **args)
{
    int error = 0;

    if (my_arraylen(args) < 2) {
        fprintf(stderr, "unalias: not enough arguments\n");
        return 1;
    }
    for (int i = 1; args[i] != NULL; i++)
        error = remove_alias(&shell->alias_list, args[i]);
    file_alias(shell->alias_list);
    return error;
}

int builtin_alias(shell_state_t *shell, char **args)
{
    int error = 0;

    if (my_arraylen(args) == 1) {
        print_alias(shell->alias_list);
        return error;
    }
    if (my_arraylen(args) == 2) {
        error = alias(shell->alias_list, args[1]);
        file_alias(shell->alias_list);
        return error;
    }
    return 0;
}
