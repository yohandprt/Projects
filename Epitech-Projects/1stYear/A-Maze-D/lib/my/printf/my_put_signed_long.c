/*
** EPITECH PROJECT, 2024
** my_put_long.c
** File description:
** my_put_long
*/

#include "../my.h"

int my_put_signed_long(long nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb > 9)
        my_put_signed_long(nb / 10);
    my_putchar((nb % 10) + '0');
}
