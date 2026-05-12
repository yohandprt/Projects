/*
** EPITECH PROJECT, 2024
** my_putnbr.c
** File description:
** my_putnbr
*/

#include "../my.h"

int my_put_unsigned_nbr(int nb)
{
    unsigned int n_temp;
    unsigned int n;
    unsigned int max = 4294967295;
    unsigned int new_nb = nb;

    if (nb < 0) {
        n_temp = -nb;
        n = max - n_temp;
        new_nb = n;
    }
    if (new_nb > 9)
        my_put_nbr(new_nb / 10);
    my_putchar((new_nb % 10) + '0');
    return n;
}
