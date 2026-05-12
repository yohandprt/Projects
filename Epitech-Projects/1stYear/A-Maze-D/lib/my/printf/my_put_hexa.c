/*
** EPITECH PROJECT, 2024
** my_put_hexa.c
** File description:
** my_put_hexa
*/

#include "../my.h"
#include <stdlib.h>
#include <stdio.h>

int find_len(int nb, int len_reste)
{
    int temp_nb = nb;

    while (temp_nb > 1) {
        temp_nb = temp_nb / 16;
        len_reste++;
    }
    return len_reste;
}

char *min_or_maj(int majuscule)
{
    char *str;

    if (majuscule == 0)
        str = "0123456789abcdef";
    if (majuscule == 1)
        str = "0123456789ABCDEF";
    return str;
}

void loop_print_hexa(int len_reste, char *hexa)
{
    for (int j = len_reste; j >= -1; j--) {
        if (j == len_reste && hexa[j] == '0')
            j--;
        my_putchar(hexa[j]);
    }
}

int my_put_hexa(int nb, int majuscule)
{
    char *caracteres = min_or_maj(majuscule);
    char *hexa;
    int reste = nb % 16;
    int len_reste = 0;
    int i = 0;

    len_reste = find_len(nb, len_reste);
    hexa = malloc(sizeof(int) * len_reste);
    if (!hexa)
        return 84;
    while (i <= len_reste) {
        reste = nb % 16;
        hexa[i] = caracteres[reste];
        nb = nb / 16;
        i++;
    }
    loop_print_hexa(len_reste, hexa);
    return len_reste;
}
