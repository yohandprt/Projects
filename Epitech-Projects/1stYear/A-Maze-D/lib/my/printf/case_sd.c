/*
** EPITECH PROJECT, 2024
** case_sd.c
** File description:
** case_sd
*/

#include "../my.h"

int case_sd(char const *format, va_list args, int i)
{
    char *str;
    int nb;

    switch (format[i + 1]) {
        case 's':
            str = va_arg(args, char *);
            my_putstr(str);
            i++;
            break;
        case 'd':
            nb = va_arg(args, int);
            my_put_nbr(nb);
            i++;
            break;
    }
    return i;
}
