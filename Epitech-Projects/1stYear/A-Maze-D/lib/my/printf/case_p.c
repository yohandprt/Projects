/*
** EPITECH PROJECT, 2024
** case_p.c
** File description:
** case_p
*/

#include "../my.h"

int case_p(char const *format, va_list args, int i)
{
    void *ptr;

    switch (format[i + 1]) {
        case 'p':
            ptr = va_arg(args, void *);
            my_put_pointer(ptr);
            i++;
            break;
    }
    return i;
}
