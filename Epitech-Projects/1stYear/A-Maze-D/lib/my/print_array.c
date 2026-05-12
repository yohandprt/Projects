/*
** EPITECH PROJECT, 2025
** print_array.c
** File description:
** print_array
*/

#include "my.h"

void print_array(char **array, char *separator)
{
    int i = 0;

    for (; array[i + 1]; i++)
        my_printf("%s%s", array[i], separator);
    my_printf("%s", array[i]);
}
