/*
** EPITECH PROJECT, 2024
** task06
** File description:
** task06
*/

#include "../../include/my.h"

void reverse(int *a, int *b)
{
    if (*b < *a)
        my_swap(a, b);
}

void my_sort_int_array(int *array, int size)
{
    int i = 0;

    for (; i < size - 1; i++){
        for (int j = 0; j < size -1; j++) {
            reverse(&array[j], &array[j + 1]);
        }
    }
}
