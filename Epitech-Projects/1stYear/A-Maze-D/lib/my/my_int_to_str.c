/*
** EPITECH PROJECT, 2024
** my_int_to_str.c
** File description:
** my_int_to_str
*/

#include "my.h"
#include <stdlib.h>

char *my_int_to_str(int nb)
{
    int size = count_int(nb);
    char *str_nb = malloc(sizeof(char) * size + 1);
    int i = 0;

    if (!str_nb)
        return NULL;
    for (i = 0; i < size; i++) {
        str_nb[i] = (nb % 10) + '0';
        nb = nb / 10;
    }
    str_nb[i] = '\0';
    my_revstr(str_nb);
    return str_nb;
}
