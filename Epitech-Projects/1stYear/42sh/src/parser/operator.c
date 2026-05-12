/*
** EPITECH PROJECT, 2024
** mainBranch
** File description:
** operator.c
*/

#include <string.h>

#include "parser.h"

static const operator_handler_t operator_handlers[] = {
    {";", SEMICOLON},
    {"|", PIPE},
    {">", REDIRECT_OUT},
    {"<", REDIRECT_IN},
    {">>", REDIRECT_APPEND},
    {"<<", REDIRECT_HEREDOC},
    {"&&", AND_OPERATOR},
    {"||", OR_OPERATOR},
    {"(", PAREN_OPEN},
    {")", PAREN_CLOSE},
    {NULL, WORD}
};

static token_type_t get_operator_type(char *op)
{
    int i = 0;

    while (operator_handlers[i].operator != NULL) {
        if (strcmp(op, operator_handlers[i].operator) == 0)
            return operator_handlers[i].type;
        i++;
    }
    return WORD;
}

static void append_to_buffer(char *input, int *i, char *buffer,
    int *buffer_index)
{
    (*i)++;
    if (input[*i] != '\0') {
        buffer[(*buffer_index)] = input[*i];
        (*buffer_index)++;
        (*i)++;
    }
}

static int handle_quoted_word(char *input, int *i, char quote_char,
    char *buffer)
{
    int buffer_index = 0;

    (*i)++;
    buffer[buffer_index] = quote_char;
    buffer_index++;
    while (input[*i] != '\0' && input[*i] != quote_char) {
        if (input[*i] == '\\' && quote_char != '\'') {
            append_to_buffer(input, i, buffer, &buffer_index);
        } else {
            buffer[buffer_index] = input[*i];
            buffer_index++;
            (*i)++;
        }
    }
    if (input[*i] == quote_char) {
        buffer[buffer_index] = quote_char;
        buffer_index++;
        (*i)++;
    }
    return buffer_index;
}

static void helper_operator(char *input, int *i, char *buffer)
{
    if ((input[*i] == '>' || input[*i] == '<') && input[*i + 1] == input[*i]) {
        buffer[0] = input[*i];
        buffer[1] = input[*i];
        buffer[2] = '\0';
        *i += 2;
    } else if ((input[*i] == '&' || input[*i] == '|') &&
            input[*i + 1] == input[*i]) {
        buffer[0] = input[*i];
        buffer[1] = input[*i];
        buffer[2] = '\0';
        *i += 2;
    } else {
        buffer[0] = input[*i];
        buffer[1] = '\0';
        (*i)++;
    }
}

void handle_word(char *input, int *i, int *start, token_list_t **head)
{
    char buffer[1024] = {0};
    int buffer_index = 0;
    bool in_word = true;

    while (in_word && input[*i] != '\0') {
        if (is_space(input[*i]) || is_operator(input[*i]))
            in_word = false;
        if (is_quote(input[*i]))
            buffer_index = handle_quoted_word(input, i, input[*i], buffer);
        buffer[buffer_index] = input[*i];
        buffer_index++;
        (*i)++;
    }
    buffer[buffer_index] = '\0';
    if (buffer_index > 0)
        add_token(head, buffer, WORD);
    *start = *i;
}

void handle_operator(char *input, int *i, int *start,
    token_list_t **head)
{
    char buffer[3] = {0};
    token_type_t type;
    char word[1024] = {0};

    if (*i > *start) {
        strncpy(word, input + *start, *i - *start);
        word[*i - *start] = '\0';
        add_token(head, word, WORD);
    }
    helper_operator(input, i, buffer);
    type = get_operator_type(buffer);
    add_token(head, buffer, type);
    *start = *i;
}

void handle_space(char *input, int *i_start[2], char *buffer,
    token_list_t **head)
{
    if (*i_start[0] > *i_start[1]) {
        strncpy(buffer, input + *i_start[1], *i_start[0] - *i_start[1]);
        buffer[*i_start[0] - *i_start[1]] = '\0';
        add_token(head, buffer, WORD);
    }
    (*i_start[0])++;
    *i_start[1] = *i_start[0];
}

void handle_parenthesis(char *input, int *i, int *start, token_list_t **head)
{
    char buffer[2] = {0};

    if (*i > *start) {
        strncpy(buffer, input + *start, *i - *start);
        buffer[*i - *start] = '\0';
        add_token(head, buffer, WORD);
    }
    buffer[0] = input[*i];
    buffer[1] = '\0';
    if (input[*i] == '(')
        add_token(head, buffer, PAREN_OPEN);
    else
        add_token(head, buffer, PAREN_CLOSE);
    (*i)++;
    *start = *i;
}
