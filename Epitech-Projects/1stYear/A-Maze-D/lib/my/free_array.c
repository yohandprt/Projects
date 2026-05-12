/*
** EPITECH PROJECT, 2025
** free_array.c
** File description:
** free_array
*/

#include <stdlib.h>

void free_array(char **array)
{
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}
