/*
** EPITECH PROJECT, 2024
** my_put_g.c
** File description:
** my_put_g
*/

#include "../my.h"
#include <stdio.h>

int my_put_g(double nb, int majuscule)
{
    int i = 0;
    int temp_nb = nb;

    while (temp_nb > 9) {
        i++;
        temp_nb /= 10;
    }
    i++;
    if (i == 6)
        my_put_nbr((int)nb);
    if (i > 6)
        my_put_e(nb, majuscule);
    if (i < 6)
        my_put_float(nb, 6);
}
