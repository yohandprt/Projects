/*
** EPITECH PROJECT, 2024
** case_g.c
** File description:
** case_g
*/

#include "../my.h"

int case_g(char const *format, va_list args, int i)
{
    float nb;

    switch (format[i + 1]) {
        case 'g':
            nb = va_arg(args, double);
            my_put_g(nb, 0);
            i++;
            break;
        case 'G':
            nb = va_arg(args, double);
            my_put_g(nb, 1);
            i++;
            break;
    }
    return i;
}
