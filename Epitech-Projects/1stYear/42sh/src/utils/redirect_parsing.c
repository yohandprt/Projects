/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-thomas.villot
** File description:
** redirect_parsing.c
*/

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "parser.h"
#include "error.h"
#include "executor.h"

static token_list_t *handle_input_redirect(token_list_t *token, command_t *cmd)
{
    cmd->in_file = strdup(token->next->token);
    cmd->heredoc = false;
    return token->next;
}

static token_list_t *handle_heredoc_redirect(token_list_t *token,
    command_t *cmd)
{
    cmd->in_file = strdup(token->next->token);
    cmd->heredoc = true;
    return token->next;
}

static token_list_t *handle_output_redirect(token_list_t *token,
    command_t *cmd)
{
    cmd->out_file = strdup(token->next->token);
    cmd->append = false;
    return token->next;
}

static token_list_t *handle_append_redirect(token_list_t *token,
    command_t *cmd)
{
    cmd->out_file = strdup(token->next->token);
    cmd->append = true;
    return token->next;
}

token_list_t *process_redirect(token_list_t *token, command_t *cmd)
{
    if (!token)
        return NULL;
    if (!token->next) {
        print_error("Missing name for redirect.\n", 1);
        return NULL;
    }
    switch (token->type) {
        case REDIRECT_OUT:
            return handle_output_redirect(token, cmd);
        case REDIRECT_APPEND:
            return handle_append_redirect(token, cmd);
        case REDIRECT_IN:
            return handle_input_redirect(token, cmd);
        case REDIRECT_HEREDOC:
            return handle_heredoc_redirect(token, cmd);
        default:
            return token;
    }
    return NULL;
}
