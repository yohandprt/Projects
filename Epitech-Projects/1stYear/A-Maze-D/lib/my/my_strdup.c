/*
** EPITECH PROJECT, 2024
** task01
** File description:
** task01
*/

#include <stdlib.h>
#include "../../include/my.h"
#include <stdio.h>

char *my_strdup(char const *src)
{
    int i;
    char *str = malloc(sizeof(char) * (my_strlen(src) + 1));

    if (str == NULL)
        return NULL;
    for (i = 0; src[i] != '\0'; i++) {
        str[i] = src[i];
    }
    str[my_strlen(src)] = '\0';
    return str;
}
