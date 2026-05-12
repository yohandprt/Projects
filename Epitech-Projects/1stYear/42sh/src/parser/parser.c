/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** Parser for command lines
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "error.h"
#include "parser.h"
#include "shell.h"
#include "utils.h"

static bool handle_pipe_token(token_list_t *current, bool *had_word)
{
    token_list_t *next = current->next;

    if (!*had_word)
        return false;
    while (next && next->type != WORD && next->type != PIPE)
        next = next->next;
    if (!next || next->type != WORD)
        return false;
    *had_word = false;
    return true;
}

static bool is_valid_pipe_sequence(token_list_t *tokens)
{
    token_list_t *current = tokens;
    bool had_word = false;

    if (current && current->type == PIPE)
        return false;
    while (current != NULL) {
        if (current->type == WORD)
            had_word = true;
        if (current->type == PIPE && !handle_pipe_token(current, &had_word))
            return false;
        current = current->next;
    }
    return true;
}

static bool validate_parentheses(token_list_t *tokens)
{
    token_list_t *current = tokens;
    int paren_count = 0;

    while (current != NULL) {
        if (current->type == PAREN_OPEN)
            paren_count++;
        if (current->type == PAREN_CLOSE)
            paren_count--;
        if (paren_count < 0)
            return false;
        current = current->next;
    }
    return paren_count == 0;
}

static void handle_quoted_string(char *input, int *i, token_list_t **head,
    char quote_char)
{
    int quote_start = *i;
    int quote_length = find_closing_quote(input, i, quote_char, quote_start);
    char *quoted_string = malloc(quote_length + 1);

    if (!quoted_string)
        return;
    strncpy(quoted_string, input + quote_start, quote_length);
    quoted_string[quote_length] = '\0';
    add_token(head, quoted_string, WORD);
    free(quoted_string);
}

static void handle_backtick_string(char *input, int *i, int *start,
    token_list_t **head)
{
    int backtick_start = *i;
    int backtick_length = 0;
    char *backtick_string = NULL;

    (*i)++;
    while (input[*i] != '\0' && input[*i] != '`')
        (*i)++;
    if (input[*i] == '`')
        (*i)++;
    backtick_length = *i - backtick_start;
    backtick_string = malloc(backtick_length + 1);
    if (!backtick_string)
        return;
    strncpy(backtick_string, input + backtick_start, backtick_length);
    backtick_string[backtick_length] = '\0';
    add_token(head, backtick_string, BACKTICK);
    free(backtick_string);
    *start = *i;
}

static char *extract_token(int idx[2], char *buffer, char *input,
    token_list_t **head)
{
    if (idx[0] > idx[1]) {
        strncpy(buffer, input + idx[1], idx[0] - idx[1]);
        buffer[idx[0] - idx[1]] = '\0';
        add_token(head, buffer, WORD);
    }
    return buffer;
}

static int handle_special_characters(char *input, int *i_start[2],
    char *buffer, token_list_t **head)
{
    if (input[*i_start[0]] == '\'') {
        extract_token(*i_start, buffer, input, head);
        handle_quoted_string(input, i_start[0], head, '\'');
        *i_start[1] = *i_start[0];
        return 1;
    }
    if (input[*i_start[0]] == '"') {
        extract_token(*i_start, buffer, input, head);
        handle_quoted_string(input, i_start[0], head, '"');
        *i_start[1] = *i_start[0];
        return 1;
    }
    if (input[*i_start[0]] == '`') {
        extract_token(*i_start, buffer, input, head);
        handle_backtick_string(input, i_start[0], i_start[1], head);
        *i_start[1] = *i_start[0];
        return 1;
    }
    return 0;
}

void add_token(token_list_t **head, char *token, token_type_t type)
{
    token_list_t *new_node = malloc(sizeof(token_list_t));
    token_list_t *current = NULL;

    if (!new_node || !token)
        return;
    new_node->token = strdup(token);
    new_node->type = type;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    current = *head;
    while (current->next != NULL)
        current = current->next;
    current->next = new_node;
}

void tokenize_input(char *input, token_list_t **head)
{
    int i = 0;
    int start = 0;
    char buffer[1024] = {0};

    while (input[i] != '\0') {
        if (is_space(input[i])) {
            handle_space(input, (int *[2]){&i, &start}, buffer, head);
            continue;
        }
        if (handle_special_characters(input,
            (int *[2]){&i, &start}, buffer, head) == 1)
            continue;
        if (is_operator(input[i]))
            handle_operator(input, &i, &start, head);
        else
            i++;
    }
    extract_token((int[2]){i, start}, buffer, input, head);
}

token_list_t *parse_command_line(char *input)
{
    token_list_t *tokens = NULL;

    if (!input || input[0] == '\0')
        return NULL;
    tokenize_input(input, &tokens);
    if (!is_valid_pipe_sequence(tokens)) {
        print_error("Invalid null command.\n", 1);
        free_token_list(tokens);
        return NULL;
    }
    if (!validate_parentheses(tokens)) {
        print_error("Unmatched parentheses.\n", 1);
        free_token_list(tokens);
        return NULL;
    }
    return tokens;
}
