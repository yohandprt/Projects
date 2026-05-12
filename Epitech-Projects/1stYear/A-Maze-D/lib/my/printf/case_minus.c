/*
** EPITECH PROJECT, 2024
** case_moins.c
** File description:
** case_moins
*/

#include "../my.h"

int case_minus(char const *format, va_list args, int i)
{
    int nb;
    int decal;

    switch (format[i + 1]) {
        case '-':
            nb = va_arg(args, int);
            decal = find_number(format, i + 1);
            if (decal == -48)
                decal = 0;
            else
                i++;
            my_put_minus(nb, decal);
            i = i + count_int(decal) + 1;
            break;
    }
    return i;
}
