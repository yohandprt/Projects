/*
** EPITECH PROJECT, 2024
** put_nbr
** File description:
** task07
*/

#include "../../include/my.h"
#include <stdio.h>
#include <stdarg.h>

int flag(const char format, va_list list)
{
    switch (format) {
        case 's':
            my_putstr(va_arg(list, char *));
            break;
        case 'c':
            my_putchar(va_arg(list, int));
            break;
        case 'd':
            my_put_nbr(va_arg(list, int));
            break;
        case 'i':
            my_put_nbr(va_arg(list, int));
            break;
        case '%':
            my_putchar('%');
    }
    return 0;
}

int mini_printf(const char *format, ...)
{
    va_list list;

    va_start(list, format);
    for (int i = 0; format[i] != '\0'; i++){
        if (format[i] == '%') {
            i++;
            flag(format[i], list);
        } else {
            my_putchar(format[i]);
        }
    }
    va_end(list);
    return 0;
}
