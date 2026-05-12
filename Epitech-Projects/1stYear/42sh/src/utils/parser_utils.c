/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** parser_utils.c
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "shell.h"

int find_closing_quote(char *input, int *i, char quote_char, int start)
{
    int quote_length = 0;

    (*i)++;
    while (input[*i] != '\0' && input[*i] != quote_char) {
        if (input[*i] == '\\' && quote_char == '"' && input[*i + 1] != '\0') {
            (*i) += 2;
        } else {
            (*i)++;
        }
    }
    if (input[*i] == quote_char)
        (*i)++;
    quote_length = *i - start;
    return quote_length;
}

static void helper_remove_quotes(char *str, int i, bool *in_quotes,
    char *quote_type)
{
    *in_quotes = !*in_quotes;
    if (*in_quotes)
        *quote_type = str[i];
    else
        *quote_type = '\0';
}

char *remove_quotes(char *str)
{
    int len = strlen(str);
    char *result = malloc(len + 1);
    int j = 0;
    bool in_quotes = false;
    char quote_type = '\0';

    if (!result)
        return NULL;
    for (int i = 0; i < len; i++) {
        if ((str[i] == '\'' || str[i] == '"') &&
                (!in_quotes || quote_type == str[i])) {
            helper_remove_quotes(str, i, &in_quotes, &quote_type);
        } else {
            result[j] = str[i];
            j++;
        }
    }
    result[j] = '\0';
    return result;
}
