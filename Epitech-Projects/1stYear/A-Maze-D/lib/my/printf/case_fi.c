/*
** EPITECH PROJECT, 2024
** case_fi.c
** File description:
** case_fi
*/

#include "../my.h"

int case_i(char const *format, va_list args, int i, int nb)
{
    if (format[i + 1] == 'i') {
        nb = va_arg(args, int);
        my_put_nbr(nb);
        i++;
    }
    return i;
}

int case_fi(char const *format, va_list args, int i)
{
    float fl;
    int nb;
    int precision = 6;

    switch (format[i + 1]) {
        case '.':
            precision = find_number(format, i + 1);
            i += 2;
        case 'f':
            fl = va_arg(args, double);
            nb = fl;
            my_put_float(fl, precision);
            i++;
            break;
        case 'i':
            i = case_i(format, args, i, nb);
            break;
    }
    return i;
}
