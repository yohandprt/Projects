/*
** EPITECH PROJECT, 2024
** case_ou.c
** File description:
** case_ou
*/

#include "../my.h"

int case_ou(char const *format, va_list args, int i)
{
    int nb;
    unsigned int u_nb;

    switch (format[i + 1]) {
        case 'o':
            nb = va_arg(args, int);
            my_put_octal(nb);
            i++;
            break;
        case 'u':
            nb = va_arg(args, unsigned int);
            u_nb = my_put_unsigned_nbr(nb);
            i++;
            break;
    }
    return i;
}
