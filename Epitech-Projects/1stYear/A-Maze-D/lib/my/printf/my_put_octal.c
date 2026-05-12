/*
** EPITECH PROJECT, 2024
** my_octal_nbr.c
** File description:
** my_octal_nbr
*/

#include "../my.h"
#include <stdlib.h>

int my_put_octal(int nb)
{
    int size = 20;
    int *reste = malloc(sizeof(int) * size);
    int i = 0;
    int len_reste;

    if (!reste)
        return 84;
    while (nb != 0) {
        reste[i] = nb % 8;
        nb /= 8;
        i++;
    }
    len_reste = i;
    for (int j = len_reste - 1; j >= 0; j--)
        my_put_nbr(reste[j]);
    free(reste);
    return len_reste;
}
