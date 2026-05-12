/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** parser.h
*/

#include "shell.h"
#include "executor.h"

#ifndef PARSER_H_
    #define PARSER_H_

    #define NBR_OF_TYPE 14

/* Token types */
typedef enum {
    WORD,            /* Regular word */
    SEMICOLON,       /* ; */
    PIPE,            /* | */
    REDIRECT_IN,     /* < */
    REDIRECT_OUT,    /* > */
    REDIRECT_APPEND, /* >> */
    REDIRECT_HEREDOC, /* << */
    SINGLE_QUOTE,    /* '...' */
    DOUBLE_QUOTE,    /* "..." */
    BACKTICK,        /* `...` */
    PAREN_OPEN,      /* ( */
    PAREN_CLOSE,     /* ) */
    AND_OPERATOR,    /* && */
    OR_OPERATOR      /* || */
} token_type_t;

/* Token linked list */
typedef struct token_list_s {
    char *token;
    token_type_t type;
    struct token_list_s *next;
    struct token_list_s *prev;
} token_list_t;

typedef struct operator_handler_s {
    char *operator;
    token_type_t type;
} operator_handler_t;

typedef struct backtick_state {
    char *input;
    char *result;
    int result_len;
    int pos;
    bool in_backticks;
    int backtick_start;
    shell_state_t *shell;
} backtick_state_t;

/* Parser functions */
token_list_t *parse_command_line(char *input);
void add_token(token_list_t **head, char *token, token_type_t type);
void free_token_list(token_list_t *head);
bool is_space(char c);
bool is_operator(char c);
bool is_quote(char c);
bool is_special_char(char c);
command_list_t *build_command_list(token_list_t *tokens, shell_state_t *shell);
void free_command_list(command_list_t *head);
command_t *create_command(void);
void free_command(command_t *cmd);

/* Parser utilities */
void handle_word(char *input, int *i, int *start, token_list_t **head);
void handle_operator(char *input, int *i, int *start, token_list_t **head);
void handle_space(char *input, int *i_start[2], char *buffer,
    token_list_t **head);
void handle_parenthesis(char *input, int *i, int *start, token_list_t **head);
char *expand_variables(char *str, shell_state_t *shell);
char *execute_backtick_command(char *cmd, shell_state_t *shell);
char *remove_quotes(char *str);
token_list_t *process_redirect(token_list_t *token, command_t *cmd);
char *find_and_replace_var(char *input, int start_idx, int *end_idx,
    shell_state_t *shell);

/* Subshell functions */
int execute_subshell(shell_state_t *shell, token_list_t *start_token,
    token_list_t **end_token);
void init_shell_state(shell_state_t *dest, shell_state_t *src);
void free_shell_state(shell_state_t *state);

#endif
