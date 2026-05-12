/*
** EPITECH PROJECT, 2024
** mini_printf.c
** File description:
** mini_printf
*/

#include <stdarg.h>
#include <stdio.h>
#include "my.h"

void algo(char const *format, va_list args)
{
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
                i = case_cpourcent(format, args, i);
                i = case_sd(format, args, i);
                i = case_ou(format, args, i);
                i = case_fi(format, args, i);
                i = case_x(format, args, i);
                i = case_p(format, args, i);
                i = case_e(format, args, i);
                i = case_g(format, args, i);
                i = case_l(format, args, i);
                i = case_minus(format, args, i);
                i = case_plus(format, args, i);
                i = case_zero(format, args, i);
        } else {
            my_putchar(format[i]);
            }
    }
}

void my_printf(char const *format, ...)
{
    va_list args;
    int cpt = 0;

    va_start(args, format);
    algo(format, args);
    va_end(args);
}
