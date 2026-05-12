/*
** EPITECH PROJECT, 2024
** task02
** File description:
** task02
*/

#include "../../include/my.h"

char *my_strncpy(char *dest, char const *src, int n)
{
    int i;

    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    if (n > my_strlen(src))
        dest[i] = '\0';
    return dest;
}
