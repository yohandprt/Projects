/*
** EPITECH PROJECT, 2024
** my_arraylen.c
** File description:
** my_arraylen
*/

#include "my.h"
#include <stdlib.h>

int my_arraylen(char **array)
{
    int i = 0;

    while (array[i] != NULL)
        i++;
    return i;
}
