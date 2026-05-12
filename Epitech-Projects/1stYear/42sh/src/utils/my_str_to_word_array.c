/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** my_str_to_word_array.c
*/

#include <stdlib.h>
#include <string.h>

#include "utils.h"

static int count_words(const char *str, const char *delimiter)
{
    int count = 0;
    char *token = NULL;
    char *copy = strdup(str);

    if (!copy)
        return 0;
    token = strtok(copy, delimiter);
    while (token) {
        count++;
        token = strtok(NULL, delimiter);
    }
    free(copy);
    return count;
}

static void fill_word_array(char **array, const char *str,
    const char *delimiter)
{
    char *copy = strdup(str);
    char *token = strtok(copy, delimiter);

    for (int i = 0; token; i++) {
        array[i] = strdup(token);
        if (!array[i]) {
            free_array(array);
            free(copy);
            return;
        }
        token = strtok(NULL, delimiter);
    }
    array[count_words(str, delimiter)] = NULL;
    free(copy);
}

char **my_str_to_word_array(const char *str, const char *delimiter)
{
    int count = 0;
    char **array = NULL;

    if (!str || !delimiter)
        return NULL;
    count = count_words(str, delimiter);
    array = malloc(sizeof(char *) * (count + 1));
    if (!array)
        return NULL;
    fill_word_array(array, str, delimiter);
    return array;
}

void free_array(char **array)
{
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}
