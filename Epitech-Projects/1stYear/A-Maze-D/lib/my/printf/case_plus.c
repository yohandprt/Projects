/*
** EPITECH PROJECT, 2024
** sign
** File description:
** sign
*/

#include "../my.h"

int case_plus(char const *format, va_list args, int i)
{
    int nb;
    int decal;

    switch (format[i + 1]) {
        case '+':
            nb = va_arg(args, int);
            decal = find_number(format, i + 1);
            if (decal == -48)
                decal = 0;
            else
                i++;
            my_put_plus(nb, decal);
            i = i + 2;
            break;
    }
    return i;
}
