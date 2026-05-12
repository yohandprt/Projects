/*
** EPITECH PROJECT, 2024
** case_x.c
** File description:
** case_x
*/

#include "../my.h"

int case_x(char const *format, va_list args, int i)
{
    int nb;

    switch (format[i + 1]) {
        case 'x':
            nb = va_arg(args, int);
            my_put_hexa(nb, 0);
            i++;
            break;
        case 'X':
            nb = va_arg(args, int);
            my_put_hexa(nb, 1);
            i++;
            break;
    }
    return i;
}
