/*
** EPITECH PROJECT, 2024
** my_isneg
** File description:
** task04
*/

#include "../../include/my.h"

int my_isneg(int n)
{
    if (n > 0 || n == 0)
        my_putchar('P');
    if (n < 0)
        my_putchar('N');
}
