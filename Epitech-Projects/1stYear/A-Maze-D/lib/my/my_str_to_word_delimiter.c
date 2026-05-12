/*
** EPITECH PROJECT, 2024
** task04
** File description:
** task04
*/

#include <stdlib.h>
#include <stdio.h>
#include "../../include/my.h"

int delimiter(char c, char const *deli)
{
    if (deli == NULL)
        return 0;
    for (int i = 0; deli[i] != '\0'; i++) {
        if (deli == NULL || deli[i] == '\0')
            return 0;
        if (c == deli[i])
            return 1;
    }
    return 0;
}

int count_words(char const *str, char const *deli)
{
    int length = 0;

    if (str == NULL)
        return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (delimiter(str[i], deli))
            continue;
        length++;
        while (str[i] != '\0' && !delimiter(str[i], deli))
            i++;
        if (str[i] == '\0')
            break;
    }
    return length;
}

char **split(char **array, int *temp, char const *str, char const *deli)
{
    if (!delimiter(str[temp[2]], deli))
            temp[1]++;
    if (temp[1] > 0 && delimiter(str[temp[2]], deli)) {
        array[temp[0]] = malloc(sizeof(char) * (temp[1] + 1));
        if (!array[temp[0]])
            return NULL;
        my_strncpy(array[temp[0]], str + temp[2] - temp[1], temp[1]);
        array[temp[0]][temp[1]] = '\0';
        temp[0]++;
        temp[1] = 0;
    }
    return array;
}

char **split_word(char **array, int src, char const *str, char const *deli)
{
    int len = 0;
    int j = 0;
    int temp[3];

    temp[0] = src;
    temp[1] = len;
    temp[2] = j;
    if (str == NULL || temp[0] == -1 || temp[1] == -1 || temp[2] == -1)
        return NULL;
    for (; str[temp[2]] != '\0'; temp[2]++)
        array = split(array, temp, str, deli);
    if (temp[1] > 0) {
        array[temp[0]] = malloc(sizeof(char) * (temp[1] + 1));
        if (!array[temp[0]])
            return NULL;
        my_strncpy(array[temp[0]], str + my_strlen(str) - temp[1], temp[1]);
        array[temp[0]][temp[1]] = '\0';
    }
    return array;
}

char **str_array_deli(char const *str, char const *deli)
{
    char **array = NULL;
    int length = count_words(str, deli);
    int src_tab = 0;

    array = malloc(sizeof(char *) * (length + 1));
    if (!array)
        return NULL;
    array = split_word(array, src_tab, str, deli);
    if (!array) {
        free(array);
        return NULL;
    }
    array[length] = NULL;
    return array;
}
