/*
** EPITECH PROJECT, 2025
** my_isdigit.c
** File description:
** my_isdigit
*/

int my_isdigit(char c)
{
    if (c < '0' || c > '9')
        return 0;
    return 1;
}
