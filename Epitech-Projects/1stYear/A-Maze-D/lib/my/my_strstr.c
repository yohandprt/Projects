/*
** EPITECH PROJECT, 2024
** my_strstr.c
** File description:
** my_strstr
*/

#include "my.h"
#include <stdlib.h>

char *my_strstr(char *str, char const *to_find)
{
    int j = 0;
    int cpt = 0;
    int len_tofind = my_strlen(to_find);
    char *find = malloc(sizeof(char) * len_tofind);

    if (!find)
        return NULL;
    if (to_find == "")
        return str;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == to_find[j]) {
            find[j] = str[i];
            j++;
            cpt++;
        }
        if (cpt == len_tofind)
            return find;
    }
    free(find);
    return NULL;
}
