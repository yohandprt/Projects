/*
** EPITECH PROJECT, 2024
** getnbr
** File description:
** task05
*/

#include <stdio.h>
#include <stdbool.h>
#include "../../include/my.h"

int check_char(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return 1;
    return 0;
}

bool find_sign(char const *str)
{
    int count = 0;
    char c;

    while (*str != '\0') {
        c = *str;
        if (c == '-')
            count++;
        str++;
    }
    return (count % 2 == 1);
}

int check_limit(int i, char stri, bool is_neg)
{
    if (i < 0 && i != -2147483648) {
        return (0);
    }
    if (i == -2147483648 && (stri != '\0' || is_neg == false)) {
        return (0);
    }
    return (1);
}

int get_nbr(char const *str, bool is_neg)
{
    int result = 0;
    bool has_num = false;
    int i;

    for (i = 0; str[i] != '\0' && result != -2147483648; i++) {
        if (!has_num && check_char(str[i]) != 1)
            has_num = 1;
        if (has_num && check_char(str[i]) == 1)
            break;
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10;
            result = result + str[i] - 48;
        }
        if (check_limit(result, str[i + 1], is_neg) == 0)
            return 0;
    }
    return result;
}

int my_getnbr(char const *str)
{
    bool is_neg = find_sign(str);
    int result;
    int i = 0;

    for (; str[i] != '\0'; i++) {
        if (str[i] == '+' || str[i] == '-')
            i++;
    }
    result = get_nbr(str, is_neg);
    if (is_neg == 1)
        result = result * -1;
    return result;
}
