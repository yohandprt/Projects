/*
** EPITECH PROJECT, 2024
** PSU
** File description:
** my_realloc.c
*/

#include "my.h"
#include <stdlib.h>
#include <string.h>

void *my_memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    if (!dest || !src || n <= 0)
        return NULL;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

void *my_realloc(void *str, int old_size, int new_size)
{
    char *new_str = NULL;
    int size_cpy = 0;

    if (new_size <= 0) {
        free(str);
        return NULL;
    }
    if (str == NULL)
        return malloc(new_size);
    new_str = malloc(new_size);
    if (new_str == NULL)
        return NULL;
    if (old_size < new_size)
        size_cpy = old_size;
    else
        size_cpy = new_size;
    my_memcpy(new_str, str, size_cpy);
    free(str);
    return new_str;
}
