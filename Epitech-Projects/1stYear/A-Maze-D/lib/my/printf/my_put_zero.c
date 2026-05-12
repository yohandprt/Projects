/*
** EPITECH PROJECT, 2024
** my_put_zero.c
** File description:
** my_put_zero
*/

#include "../my.h"

int my_put_zero(int nb, int decal)
{
    int len = count_int(nb);

    if (decal <= len) {
        my_put_nbr(nb);
        return len;
    }
    decal -= len;
    for (int i = 0; i < decal; i++)
        my_put_nbr(0);
    my_put_nbr(nb);
    return count_int(nb) + 1 + decal;
}
