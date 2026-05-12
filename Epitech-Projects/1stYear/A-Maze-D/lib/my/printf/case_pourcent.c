/*
** EPITECH PROJECT, 2024
** case_pourcent.c
** File description:
** case_pourcent
*/

#include "../my.h"

int case_cpourcent(char const *format, va_list args, int i)
{
    char c;
    int nb;

    switch (format[i + 1]) {
        case 'c':
            c = va_arg(args, int);
            my_putchar(c);
            i++;
            break;
        case '%':
            my_putchar('%');
            break;
    }
    return i;
}
