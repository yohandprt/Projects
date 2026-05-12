/*
** EPITECH PROJECT, 2024
** case_e.c
** File description:
** case_e
*/

#include "../my.h"

int case_e(char const *format, va_list args, int i)
{
    float nb;

    switch (format[i + 1]) {
        case 'e':
            nb = va_arg(args, double);
            my_put_e(nb, 0);
            i++;
            break;
        case 'E':
            nb = va_arg(args, double);
            my_put_e(nb, 1);
            i++;
            break;
    }
    return i;
}
