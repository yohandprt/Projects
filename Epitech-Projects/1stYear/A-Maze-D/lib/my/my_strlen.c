/*
** EPITECH PROJECT, 2024
** strlen
** File description:
** task03
*/

#include "../../include/my.h"

int my_strlen(char const *str)
{
    int temp = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        temp = i + 1;
    }
    return temp;
}
