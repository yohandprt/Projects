/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-thomas.villot
** File description:
** mal_strcat.c
*/

#include <unistd.h>
#include <stdlib.h>
#include "../../include/my.h"

char *malloc_strcat(char *str, char *dest)
{
    int len_s = my_strlen(str);
    int len_d = my_strlen(dest);
    char *cat = malloc(sizeof(char) * (len_s + len_d + 2));
    int j = 0;

    if (!cat)
        return NULL;
    for (int i = 0; str[i]; i++) {
        cat[j] = str[i];
        j++;
    }
    cat[j] = '/';
    j++;
    for (int i = 0; dest[i]; i++) {
        cat[j] = dest[i];
        j++;
    }
    cat[j] = '\0';
    return cat;
}
