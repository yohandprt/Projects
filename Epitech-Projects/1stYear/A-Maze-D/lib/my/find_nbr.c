/*
** EPITECH PROJECT, 2024
** find_number.c
** File description:
** find_number
*/

#include <stdlib.h>
#include "my.h"

char find_letter(char const *format, int debut)
{
    int i = 0;

    while (format[debut + i] < 'a' || format[debut +i] > 'z')
        i++;
    return format[debut + i];
}

int find_number(char const *format, int debut)
{
    int i = 0;
    char *str_nb;
    int nb;
    char letter = find_letter(format, debut);

    while (format[debut + i] != letter)
        i++;
    str_nb = malloc(sizeof(char) * i);
    if (!str_nb)
        return -1;
    if (i == 1) {
        nb = 1;
    }
    for (int j = 1; format[debut + j] != format[debut + i]; j++)
        str_nb[j - 1] = format[debut + j];
    nb = my_str_to_int(str_nb);
    return nb;
}
