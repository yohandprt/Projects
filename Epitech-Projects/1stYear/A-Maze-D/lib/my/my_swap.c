/*
** EPITECH PROJECT, 2024
** my_swap
** File description:
** task01
*/

#include "../../include/my.h"

void my_swap(int *a, int *b)
{
    int c = *b;

    *b = *a;
    *a = c;
}
