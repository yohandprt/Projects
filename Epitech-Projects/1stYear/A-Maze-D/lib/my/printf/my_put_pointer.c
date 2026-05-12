/*
** EPITECH PROJECT, 2024
** my_put_pointer.c
** File description:
** my_put_pointer
*/

#include "../my.h"
#include <stdio.h>

int put_hexa(unsigned long nb)
{
    char *caracteres = "0123456789abcdef";
    char hexa[16];
    int reste = nb % 16;
    int i = 0;

    while (i <= 16) {
        reste = nb % 16;
        hexa[i] = caracteres[reste];
        nb = nb / 16;
        i++;
    }
    my_putstr("0x");
    for (int j = 12; j >= -1; j--) {
        if (j == 12 && hexa[j] == '0')
            j--;
        my_putchar(hexa[j]);
    }
    return 12;
}

int my_put_pointer(void *p)
{
    unsigned long ptr = (unsigned long)p;
    int i = put_hexa(ptr);

    return i;
}
