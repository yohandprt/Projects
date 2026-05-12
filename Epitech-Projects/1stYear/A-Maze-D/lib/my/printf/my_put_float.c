/*
** EPITECH PROJECT, 2024
** my_put_float.c
** File description:
** my_put_float
*/

#include "../my.h"

void put_point(int precision)
{
    if (precision > 0)
        my_putchar('.');
}

int my_put_float(double nb, int precision)
{
    int size = 6;
    int nb_int = nb;
    int decimales[precision];
    int temp;
    int i = 0;

    my_put_nbr(nb_int);
    nb = nb - nb_int;
    put_point(precision);
    while (i < precision) {
        nb = nb * 10;
        nb_int = nb + 1;
        if (nb_int == 0)
            my_put_nbr(0);
        else
            my_put_nbr(nb_int);
        nb = nb - nb_int;
        i++;
    }
    return i;
}
