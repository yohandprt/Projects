/*
** EPITECH PROJECT, 2024
** mainBranch
** File description:
** operator_utils.c
*/

#include <stdbool.h>

bool is_quote(char c)
{
    return (c == '\'' || c == '"' || c == '`');
}

bool is_special_char(char c)
{
    return (c == '(' || c == ')');
}

bool is_operator(char c)
{
    return (c == ';' || c == '|' || c == '>' || c == '<' ||
        c == '&' || c == '(' || c == ')');
}

bool is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}
