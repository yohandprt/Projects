/*
** EPITECH PROJECT, 2024
** count_int.c
** File description:
** count_int
*/

#include "my.h"

int count_int(int nb)
{
    int i = 0;
    int temp = nb;

    while (temp > 9) {
        temp /= 10;
        i++;
    }
    return i + 1;
}
