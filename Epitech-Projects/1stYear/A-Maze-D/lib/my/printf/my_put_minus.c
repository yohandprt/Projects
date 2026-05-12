/*
** EPITECH PROJECT, 2024
** my_put_moins.c
** File description:
** my_put_moins
*/

#include "../my.h"

int my_put_minus(int nb, int decal)
{
    int len = count_int(nb);

    if (decal <= len) {
        my_put_nbr(nb);
        return len;
    }
    decal -= len;
    my_put_nbr(nb);
    for (int i = 0; i < decal; i++)
        my_putchar(' ');
    return decal + len;
}
