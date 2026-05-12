/*
** EPITECH PROJECT, 2024
** my_put_longlong.c
** File description:
** my_put_longlong
*/

#include "../my.h"

int my_put_signed_longlong(long long nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb > 9)
        my_put_signed_longlong(nb / 10);
    my_putchar((nb % 10) + '0');
}
