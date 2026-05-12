/*
** EPITECH PROJECT, 2024
** case_l.c
** File description:
** case_l
*/

#include "../my.h"

int other_cases(char const *format, va_list args, int i)
{
    long lnb;
    long long llnb;

    if (format[i + 1] == 'd' || format[i + 1] == 'i') {
        lnb = va_arg(args, long);
        my_put_signed_long(lnb);
    }
    if (format[i + 1] == 'u') {
        lnb = va_arg(args, long);
        my_put_unsigned_long(lnb);
    }
    if (format[i + 1] == 'l') {
        i++;
        llnb = va_arg(args, long long);
        if (format[i + 1] == 'd' || format[i + 1] == 'i')
            my_put_signed_longlong(llnb);
        if (format[i + 1] == 'u')
            my_put_unsigned_longlong(llnb);
    }
    return i;
}

int case_l(char const *format, va_list args, int i)
{
    switch (format[i + 1]) {
        case 'l':
            i++;
            i = other_cases(format, args, i);
            i++;
            break;
    }
    return i;
}
