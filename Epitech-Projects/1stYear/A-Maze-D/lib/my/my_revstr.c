/*
** EPITECH PROJECT, 2024
** task01
** File description:
** task03
*/

#include <stdio.h>
#include "../../include/my.h"

char *my_revstr(char *str)
{
    int i = 0;
    int rev = my_strlen(str) - 1;
    char temp;

    for (; i < rev; i++) {
        temp = str[i];
        str[i] = str[rev];
        str[rev] = temp;
        rev--;
    }
    return str;
}
