/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** repeat.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "executor.h"
#include "utils.h"
#include "error.h"

char *init_str(char **args)
{
    char *str = NULL;
    int nb_char = 0;

    if (!args || !(args[2]))
        return NULL;
    for (int i = 2; args[i]; i++)
        nb_char += strlen(args[i]);
    str = malloc(sizeof(char) * (nb_char + 1));
    return str;
}

char *array_to_str(char **args)
{
    char *str = init_str(args);
    int index = 0;

    if (!str)
        return NULL;
    for (int i = 2; args[i]; i++) {
        for (int j = 0; args[i][j] != '\0'; j++) {
            str[index] = args[i][j];
            index++;
        }
    }
    str[index] = '\0';
    return str;
}

int check_numbers_in_str(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

int my_repeat(shell_state_t *shell, char **args)
{
    char *str = NULL;
    long loop_time = 0;
    char *end;

    if (!args || !(args[1]) || !(args[2]))
        return print_error("repeat: Too few arguments.\n", 1);
    if (!check_numbers_in_str(args[1]))
        return print_error("repeat: Badly formed number.\n", 1);
    loop_time = strtol(args[1], &end, 0);
    if (loop_time <= 0)
        return SUCCESS;
    str = array_to_str(args);
    for (long i = 0; i < loop_time; i++)
        execute_command_line(shell, str);
    free(str);
    return SUCCESS;
}
