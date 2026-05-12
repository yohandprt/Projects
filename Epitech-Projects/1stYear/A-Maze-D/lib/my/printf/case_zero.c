/*
** EPITECH PROJECT, 2024
** case_zero.c
** File description:
** case_zero
*/

#include "../my.h"

int case_zero(char const *format, va_list args, int i)
{
    int nb;
    int decal;

    switch (format[i + 1]) {
        case '0':
            nb = va_arg(args, int);
            decal = find_number(format, i + 1);
            if (decal == -48)
                decal = 0;
            else
                i++;
            my_put_zero(nb, decal);
            i = i + 2;
            break;
    }
    return i;
}
