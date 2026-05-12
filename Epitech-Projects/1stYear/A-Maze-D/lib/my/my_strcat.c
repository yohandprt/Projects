/*
** EPITECH PROJECT, 2024
** strcat
** File description:
** strcat
*/

#include "../../include/my.h"

char *my_strcat(char *dest, char const *src)
{
    int count = 0;
    int i = 0;

    for (; dest[i] != '\0'; i++)
        count += 1;
    i = 0;
    for (; src[i] != '\0'; i++)
        dest[i + count] = src[i];
    dest[i + count] = '\0';
    return dest;
}
