/*
** EPITECH PROJECT, 2024
** my_str_to_int.c
** File description:
** my_str_to_int
*/

#include "my.h"

int my_str_to_int(char const *str)
{
    int nb = 0;
    int i = 0;

    while (str[i] != '\0') {
        if ((str[i] < '0' || str[i] > '9') && str[i] != '\n')
            return -1;
        if (str[i] != '\n')
            nb = nb * 10 + (str[i] - '0');
        i++;
    }
    return nb;
}
