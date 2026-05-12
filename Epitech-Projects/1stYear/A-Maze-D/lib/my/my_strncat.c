/*
** EPITECH PROJECT, 2024
** strncat
** File description:
** strncat
*/

#include "../../include/my.h"

char *my_strncat(char *dest, char const *src, int nb)
{
    int count = 0;

    for (int i = 0; dest[i] != '\0'; i++)
        count += 1;
    for (int i = 0; src[i] != '\0' && i < nb; i++)
        dest[i + count] = src[i];
    return dest;
}
