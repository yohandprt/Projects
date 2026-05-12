/*
** EPITECH PROJECT, 2024
** plus
** File description:
** plus
*/

#include "../my.h"

int my_put_plus(int nb, int decal)
{
    int len = count_int(nb);

    decal--;
    if (decal <= len) {
        my_putchar('+');
        my_put_nbr(nb);
        return len;
    }
    decal -= len;
    for (int i = 0; i < decal; i++)
        my_putchar(' ');
    if (nb > 0)
        my_putchar('+');
    my_put_nbr(nb);
    return count_int(nb) + 1 + decal;
}
