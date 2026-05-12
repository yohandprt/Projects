/*
** EPITECH PROJECT, 2024
** my_put_e.c
** File description:
** my_put_e
*/

#include <stdio.h>
#include <float.h>
#include "../my.h"

int my_put_e(double nb, int majuscule)
{
    int i = 0;

    while (nb > 9) {
        nb /= 10;
        i++;
    }
    my_put_float(nb, 6);
    if (majuscule == 0)
        my_putstr("e+");
    if (majuscule == 1)
        my_putstr("E+");
    if (i < 10)
        my_put_nbr(0);
    my_put_nbr(i);
}
