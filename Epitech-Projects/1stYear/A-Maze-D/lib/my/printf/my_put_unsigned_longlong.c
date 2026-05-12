/*
** EPITECH PROJECT, 2024
** my_put_unsigned_longlong.c
** File description:
** my_put_unsigned_longlong
*/

#include "../my.h"

int my_put_unsigned_longlong(long long nb)
{
    unsigned long long n_temp;
    unsigned long long n;
    unsigned long long max = 1844674407370955161;
    unsigned long long new_nb = nb;

    if (nb < 0) {
        n_temp = -nb;
        n = max - n_temp;
        new_nb = n;
    }
    if (new_nb > 9)
        my_put_signed_longlong(new_nb / 10);
    my_putchar((new_nb % 10) + '0');
    return n;
}
