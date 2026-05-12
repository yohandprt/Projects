/*
** EPITECH PROJECT, 2024
** my_put_unsigned_long.c
** File description:
** my_put_unsigned_long
*/

#include "../my.h"

int my_put_unsigned_long(long nb)
{
    unsigned long n_temp;
    unsigned long n;
    unsigned long max = 1844674407370955161;
    unsigned long new_nb = nb;

    if (nb < 0) {
        n_temp = -nb;
        n = max - n_temp;
        new_nb = n;
    }
    if (new_nb > 9)
        my_put_signed_long(new_nb / 10);
    my_putchar((new_nb % 10) + '0');
    return n;
}
